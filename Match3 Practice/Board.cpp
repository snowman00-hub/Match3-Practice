#include "stdafx.h"
#include "Board.h"
#include "SceneGame.h"
#include "Tile.h"
#include "Block.h"
#include "StageUI.h"

void Board::SetBoardBlock(int* arr)
{
	BlockTypes blockType;
	BlockTypes temp;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			blockType = (BlockTypes)arr[9 * y + x];
			maxPaintableCount++;

			if (blockType == BlockTypes::Jem)
			{
				do
				{			
					blocks[y][x]->SetBlockType((BlockTypes)Utils::RandomRange(2,6));
					temp = blocks[y][x]->GetBlockType();
				} while (
					(x >= 2 && blocks[y][x - 2]->GetBlockType() == temp && blocks[y][x - 1]->GetBlockType() == temp) ||
					(y >= 2 && blocks[y - 2][x]->GetBlockType() == temp && blocks[y - 1][x]->GetBlockType() == temp)
					);
			}
			else 
			{				
				blocks[y][x]->SetBlockType(blockType);
				blocks[y][x]->SetCanMove(false);

				if (blockType == BlockTypes::None)
				{
					blocks[y][x]->SetActive(false);
					maxPaintableCount--;
				}
				else if (blockType == BlockTypes::Wall)
				{
					scene->remainWallCount++;
				}
			}
			blocks[y][x]->SetBoardPos({ x,y });
			blocks[y][x]->SetPosition({ boardLeft + (float)Block::SIZE * x, boardTop + (float)Block::SIZE * y });
		}
	}

	if (!CheckMatchPossible())
	{
		RelocateBoard();
	}
}

void Board::SetBoardTile(int* arr)
{
	TileTypes tileType;
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			tileType = (TileTypes)arr[9 * y + x];

			if (tileType == TileTypes::None || blocks[y][x]->GetBlockType() == BlockTypes::None)
			{
				tiles[y][x]->SetActive(false);
				tiles[y][x]->SetTileType(TileTypes::None);
			}
			else
			{
				tiles[y][x]->SetTileType(tileType);
				if (tileType == TileTypes::Painted)
					paintedCount++;
			}
			tiles[y][x]->SetBoardPos({ x,y });
			tiles[y][x]->SetPosition({ boardLeft + (float)Tile::SIZE * x, boardTop + (float)Tile::SIZE * y });
		}
	}

	if (paintedCount == 0)
		maxPaintableCount = 0;

	scene->remainTileCount = maxPaintableCount - paintedCount;
}

void Board::Idle()
{
	if (scene->remainTileCount == 0 && scene->remainWallCount == 0)
	{
		scene->isClear = true;
		SOUND_MGR.PlaySfx("sound/clear.mp3");
		return;
	}
	else if (scene->swapCount == 0)
	{
		scene->isDefeat = true;
		SOUND_MGR.PlaySfx("sound/defeat.mp3");
		return;
	}

	mousePos = InputMgr::GetMousePosition();

	if (mousePos.x >= boardLeft && mousePos.x < boardLeft + Block::SIZE * cols
		&& mousePos.y >= boardTop && mousePos.y < boardTop + Block::SIZE * rows)
	{
		if (InputMgr::GetMouseButton(sf::Mouse::Left))
		{
			int x = (mousePos.x - boardLeft) / Block::SIZE;
			int y = (mousePos.y - boardTop) / Block::SIZE;

			if (blocks[y][x] && !selectedBlock && blocks[y][x]->GetCanMove())
			{
				selectedBlock = blocks[y][x];
			}
			else if (blocks[y][x] && selectedBlock != blocks[y][x])
			{
				if (blocks[y][x]->GetCanMove())
					targetBlock = blocks[y][x];
				else
					selectedBlock = nullptr;
			}
		}
	}

	if (selectedBlock && targetBlock)
	{
		sf::Vector2i selectedPos = selectedBlock->GetBoardPos();
		sf::Vector2i targetPos = targetBlock->GetBoardPos();
		sf::Vector2i moveDir = targetPos - selectedPos;
		if (moveDir == sf::Vector2i(1, 1) || moveDir == sf::Vector2i(-1,1))
		{
			moveDir = sf::Vector2i(0, 1);
			targetBlock = blocks[selectedPos.y + 1][selectedPos.x];
			targetPos = targetBlock->GetBoardPos();
		}
		else if (moveDir == sf::Vector2i(1, -1) || moveDir == sf::Vector2i(-1, -1))
		{
			moveDir = sf::Vector2i(0, -1);
			targetBlock = blocks[selectedPos.y - 1][selectedPos.x];
			targetPos = targetBlock->GetBoardPos();
		}

		blocks[selectedPos.y][selectedPos.x] = targetBlock;
		blocks[targetPos.y][targetPos.x] = selectedBlock;

		selectedBlock->SetBoardPos(targetPos);
		targetBlock->SetBoardPos(selectedPos);
		selectedBlock->SetMoveDir((sf::Vector2f)(moveDir));
		targetBlock->SetMoveDir((sf::Vector2f)(-moveDir));

		selectedBlock->SetIsSwapping(true);
		targetBlock->SetIsSwapping(true);
		isSwapping = true;

		currentState = GameState::Animation;
		nextState = GameState::Swap;
		scene->swapCount--;
		((StageUI*)scene->FindGameObject("UI"))->UpdateSwapCount();
		SOUND_MGR.PlaySfx("sound/swapSound.mp3");
	}

	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
	{
		if (selectedBlock && (selectedBlock->GetBlockType() == BlockTypes::Diamond ||
			selectedBlock->GetBlockType() == BlockTypes::Emerald))
		{
			removeBlocks.insert(selectedBlock);
			currentState = GameState::Remove;
			scene->swapCount--;
			((StageUI*)scene->FindGameObject("UI"))->UpdateSwapCount();
		}

		selectedBlock = nullptr;
	}
}

void Board::SwapBlock()
{
	bool isSpecialBlock = false;
	if (selectedBlock->GetBlockType() == BlockTypes::Diamond || selectedBlock->GetBlockType() == BlockTypes::Emerald)
	{
		removeBlocks.insert(selectedBlock);
		isSpecialBlock = true;
	}

	if (targetBlock->GetBlockType() == BlockTypes::Diamond || targetBlock->GetBlockType() == BlockTypes::Emerald)
	{
		removeBlocks.insert(targetBlock);
		isSpecialBlock = true;
	}

	bool isMatchS = CheckMatchAt(selectedBlock->GetBoardPos());
	bool isMatchT = CheckMatchAt(targetBlock->GetBoardPos());

	if (isMatchS || isMatchT || isSpecialBlock)
	{
		isSwapping = false;
		selectedBlock = nullptr;
		targetBlock = nullptr;
		currentState = GameState::Remove;
	}
	else
	{
		sf::Vector2i selectedPos = selectedBlock->GetBoardPos();
		sf::Vector2i targetPos = targetBlock->GetBoardPos();

		blocks[selectedPos.y][selectedPos.x] = targetBlock;
		blocks[targetPos.y][targetPos.x] = selectedBlock;

		selectedBlock->SetBoardPos(targetPos);
		targetBlock->SetBoardPos(selectedPos);

		selectedBlock->SetMoveDir((sf::Vector2f)(targetPos - selectedPos));
		targetBlock->SetMoveDir((sf::Vector2f)(selectedPos - targetPos));

		selectedBlock->SetIsSwapping(true);
		targetBlock->SetIsSwapping(true);

		currentState = GameState::Animation;
		nextState = GameState::Idle;
	}
}

void Board::Animation(float dt)
{
	aniTimer += dt;
	if (isSwapping)
	{
		if (aniTimer > Block::swapDuration)
		{
			sf::Vector2i pos = selectedBlock->GetBoardPos();
			selectedBlock->SetPosition({ boardLeft + (float)Block::SIZE * pos.x, boardTop + (float)Block::SIZE * pos.y });
			selectedBlock->SetMoveDir({ 0.f,0.f });
			selectedBlock->SetIsSwapping(false);

			pos = targetBlock->GetBoardPos();
			targetBlock->SetPosition({ boardLeft + (float)Block::SIZE * pos.x, boardTop + (float)Block::SIZE * pos.y });
			targetBlock->SetMoveDir({ 0.f,0.f });
			targetBlock->SetIsSwapping(false);

			aniTimer = 0.f;
			currentState = nextState;

			if (nextState != GameState::Swap)
			{
				isSwapping = false;
				selectedBlock = nullptr;
				targetBlock = nullptr;
			}
		}
	}
	else if (isRemoving)
	{
		if (aniTimer > Block::removeDuration)
		{
			aniTimer = 0.f;
			isRemoving = false;

			StageTargetUIUpdate();

			RemoveBlocksUpdate();

			currentState = nextState;
		}
	}
	else if (isDropping)
	{
		if (aniTimer > Block::dropDuration)
		{
			aniTimer = 0.f;
			isDropping = false;

			for (auto block : dropBlocks)
			{
				sf::Vector2i pos = block->GetBoardPos();
				block->SetPosition({ boardLeft + (float)Block::SIZE * pos.x, boardTop + (float)Block::SIZE * pos.y });
				block->SetIsDropping(false);
				block->SetMoveDir({ 0.f,0.f });
			}
			dropBlocks.clear();
				
			currentState = nextState;
		}
	}
}

bool Board::CheckMatchAt(sf::Vector2i pos)
{
	int x = pos.x;
	int y = pos.y;
	int matchCountH = 1;
	int matchCountV = 1;
	bool isMatch = false;

	if (!blocks[y][x])
		return false;

	BlockTypes type = blocks[y][x]->GetBlockType();

	if (type == BlockTypes::None)
		return false;
	if (type == BlockTypes::Wall)
		return false;

	std::vector<sf::Vector2i> tempPos;
	tempPos.push_back(pos);

	// 가로 검사
	int nx = x;
	while (true)
	{
		nx--;
		if (nx < 0)
			break;

		if (blocks[y][nx] && type == blocks[y][nx]->GetBlockType())
		{
			tempPos.push_back(sf::Vector2i(nx, y));
			matchCountH++;
		}
		else
		{
			break;
		}
	}
	nx = x;
	while (true)
	{
		nx++;
		if (nx >= cols)
			break;

		if (blocks[y][nx] && type == blocks[y][nx]->GetBlockType())
		{
			tempPos.push_back(sf::Vector2i(nx, y));
			matchCountH++;
		}
		else
		{
			break;
		}
	}

	if (matchCountH >= 3)
	{
		bool isPainted = false;
		isMatch = true;

		for (auto pos : tempPos)
		{
			removeBlocks.insert(blocks[pos.y][pos.x]);
			CheckObstacleNeighbors(pos);
			if (tiles[pos.y][pos.x]->GetTileType() == TileTypes::Painted)
				isPainted = true;
		}

		if (isPainted)
		{
			for (auto pos : tempPos)
				paintTiles.insert(tiles[pos.y][pos.x]);
		}

		tempPos.clear();
	}
	else
	{
		tempPos.clear();
		tempPos.push_back(pos);
	}

	// 세로 검사
	int ny = y;
	while (true)
	{
		ny--;
		if (ny < 0)
			break;

		if (blocks[ny][x] && type == blocks[ny][x]->GetBlockType())
		{
			tempPos.push_back(sf::Vector2i(x, ny));
			matchCountV++;
		}
		else
		{
			break;
		}
	}
	ny = y;
	while (true)
	{
		ny++;
		if (ny >= rows)
			break;

		if (blocks[ny][x] && type == blocks[ny][x]->GetBlockType())
		{
			tempPos.push_back(sf::Vector2i(x, ny));
			matchCountV++;
		}
		else
		{
			break;
		}
	}

	if (matchCountV >= 3)
	{
		bool isPainted = false;
		isMatch = true;
		for (auto pos : tempPos)
		{
			removeBlocks.insert(blocks[pos.y][pos.x]);
			CheckObstacleNeighbors(pos);
			if (tiles[pos.y][pos.x]->GetTileType() == TileTypes::Painted)
				isPainted = true;
		}

		if (isPainted)
		{
			for (auto pos : tempPos)
				paintTiles.insert(tiles[pos.y][pos.x]);
		}
	}

	if (matchCountH >= 3 && matchCountV >= 3)
	{
		removeBlocks.erase(blocks[pos.y][pos.x]);
		blocks[pos.y][pos.x]->SetBlockType(BlockTypes::Emerald);
	}
	else if (matchCountH >= 4 || matchCountV >= 4)
	{
		removeBlocks.erase(blocks[pos.y][pos.x]);
		blocks[pos.y][pos.x]->SetBlockType(BlockTypes::Diamond);
	}

	return isMatch;
}

void Board::CheckMatchAll()
{
	bool isMatch = false;
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			if (CheckMatchAt(sf::Vector2i(x, y)))
				isMatch = true;
		}
	}

	if (isMatch)
	{
		currentState = GameState::Remove;
	}
	else
	{
		currentState = GameState::Idle;
		if (!CheckMatchPossible())
		{
			RelocateBoard();
		}
	}
}

void Board::CheckObstacleNeighbors(sf::Vector2i pos)
{
	int x = pos.x;
	int y = pos.y;
	int dx[4] = { 0,0,-1,1 };
	int dy[4] = { -1,1,0,0, };
	for (int i = 0; i < 4; ++i)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx < 0 || nx > cols - 1 || ny < 0 || ny > rows - 1)
			continue;

		if (blocks[ny][nx] && blocks[ny][nx]->GetBlockType() == BlockTypes::Wall)
		{
		   removeBlocks.insert(blocks[ny][nx]);
		   destroyedWalls.insert(blocks[ny][nx]);
		}
	}
}

void Board::CheckSpecialBlockRemoved()
{
	for (auto block : removeBlocks)
	{
		if (block->GetBlockType() == BlockTypes::Diamond)
		{
			sf::Vector2i pos = block->GetBoardPos();
			bool isPainted = tiles[pos.y][pos.x]->GetTileType() == TileTypes::Painted;
			for (int i = 0; i < cols; ++i)
			{
				if (blocks[pos.y][i] && blocks[pos.y][i]->GetBlockType() != BlockTypes::None)
				{
					nextRemoveBlocks.insert(blocks[pos.y][i]);

					if (isPainted)
						paintTiles.insert(tiles[pos.y][i]);

					if (blocks[pos.y][i]->GetBlockType() == BlockTypes::Wall)
						destroyedWalls.insert(blocks[pos.y][i]);
				}
			}
			for (int i = 0; i < rows; ++i)
			{
				if (blocks[i][pos.x] && blocks[i][pos.x]->GetBlockType() != BlockTypes::None)
				{
					nextRemoveBlocks.insert(blocks[i][pos.x]);

					if (isPainted)
						paintTiles.insert(tiles[i][pos.x]);

					if (blocks[i][pos.x]->GetBlockType() == BlockTypes::Wall)
						destroyedWalls.insert(blocks[i][pos.x]);
				}
			}
		}

		if (block->GetBlockType() == BlockTypes::Emerald)
		{
			sf::Vector2i pos = block->GetBoardPos();
			bool isPainted = tiles[pos.y][pos.x]->GetTileType() == TileTypes::Painted;
			for (int y = pos.y - 2; y <= pos.y + 2; ++y)
			{
				for (int x = pos.x - 2; x <= pos.x + 2; ++x)
				{
					if (x < 0 || x > cols - 1 || y < 0 || y > rows - 1)
						continue;

					if (blocks[y][x] && blocks[y][x]->GetBlockType() != BlockTypes::None)
					{
						nextRemoveBlocks.insert(blocks[y][x]);

						if (isPainted)
							paintTiles.insert(tiles[y][x]);

						if (blocks[y][x]->GetBlockType() == BlockTypes::Wall)
							destroyedWalls.insert(blocks[y][x]);
					}
				}
			}
		}
	}

	for (auto block : removeBlocks)
	{
		nextRemoveBlocks.erase(block);
	}
}

bool Board::CheckMatchPossible()
{
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			if (x != 0)
			{
				if (!blocks[y][x] || !blocks[y][x - 1])
					continue;

				BlockTypes temp1 = blocks[y][x]->GetBlockType();
				BlockTypes temp2 = blocks[y][x - 1]->GetBlockType();
				blocks[y][x]->SetBlockType(temp2);
				blocks[y][x - 1]->SetBlockType(temp1);
				if(CheckMatchAtPossible(blocks[y][x - 1]->GetBoardPos()) ||
				   CheckMatchAtPossible(blocks[y][x]->GetBoardPos()))
				{
					blocks[y][x]->SetBlockType(temp1);
					blocks[y][x - 1]->SetBlockType(temp2);
					return true;
				}

				blocks[y][x]->SetBlockType(temp1);
				blocks[y][x - 1]->SetBlockType(temp2);
			}

			if (y != 0)
			{
				if (!blocks[y][x] || !blocks[y - 1][x])
					continue;

				BlockTypes temp1 = blocks[y][x]->GetBlockType();
				BlockTypes temp2 = blocks[y - 1][x]->GetBlockType();
				blocks[y][x]->SetBlockType(temp2);
				blocks[y - 1][x]->SetBlockType(temp1);
				if (CheckMatchAtPossible(blocks[y - 1][x]->GetBoardPos()) ||
					CheckMatchAtPossible(blocks[y][x]->GetBoardPos()))
				{
					blocks[y][x]->SetBlockType(temp1);
					blocks[y - 1][x]->SetBlockType(temp2);
					return true;
				}

				blocks[y][x]->SetBlockType(temp1);
				blocks[y - 1][x]->SetBlockType(temp2);
			}
		}
	}
	return false;
}

bool Board::CheckMatchAtPossible(sf::Vector2i pos)
{
	int y = pos.y;
	int x = pos.x;
	int matchCountH = 1;
	int matchCountV = 1;

	if (!blocks[y][x])
		return false;

	BlockTypes type = blocks[y][x]->GetBlockType();

	if (type == BlockTypes::None || type == BlockTypes::Wall)
		return false;
	if (type == BlockTypes::Diamond || type == BlockTypes::Emerald)
		return true;

	// 가로 검사
	int nx = x;
	while (true)
	{
		nx--;
		if (nx < 0)
			break;

		if (blocks[y][nx] && type == blocks[y][nx]->GetBlockType())
		{
			matchCountH++;
		}
		else
		{
			break;
		}
	}
	nx = x;
	while (true)
	{
		nx++;
		if (nx >= cols)
			break;

		if (blocks[y][nx] && type == blocks[y][nx]->GetBlockType())
		{
			matchCountH++;
		}
		else
		{
			break;
		}
	}

	if (matchCountH >= 3)
	{
		return true;
	}

	// 세로 검사
	int ny = y;
	while (true)
	{
		ny--;
		if (ny < 0)
			break;

		if (blocks[ny][x] && type == blocks[ny][x]->GetBlockType())
		{
			matchCountV++;
		}
		else
		{
			break;
		}
	}
	ny = y;
	while (true)
	{
		ny++;
		if (ny >= rows)
			break;

		if (blocks[ny][x] && type == blocks[ny][x]->GetBlockType())
		{
			matchCountV++;
		}
		else
		{
			break;
		}
	}

	if (matchCountV >= 3)
	{
		return true;
	}

	return false;
}

void Board::RemoveBlocks()
{
	CheckSpecialBlockRemoved();	

	for (auto block : removeBlocks)
	{
		block->SetIsRemoving(true);
		block->PlaySparkle();
	}

	for (auto tile : paintTiles)
	{
		if (tile->GetTileType() != TileTypes::Painted)
		{
			tile->SetTileType(TileTypes::Painted);
			paintedCount++;
		}
	}
	paintTiles.clear();

	isRemoving = true;

	currentState = GameState::Animation;
	SOUND_MGR.PlaySfx("sound/pop.mp3");
	if (!nextRemoveBlocks.empty())
	{
		nextState = GameState::Remove;
	}
	else
	{
		nextState = GameState::Drop;
	}
}

void Board::DropBlocks()
{
	bool isDropCheck = false;
	for (int y = rows - 1; y >= 1; --y)
	{
		for (int x = cols - 1; x >= 0; --x)
		{
			if (!blocks[y][x] && blocks[y - 1][x])
			{
				if (blocks[y - 1][x]->GetCanMove())
				{
					blocks[y][x] = blocks[y - 1][x];
					blocks[y - 1][x] = nullptr;
					blocks[y][x]->SetMoveDir({ 0.f,1.f });
					blocks[y][x]->SetBoardPos({ x,y });
					blocks[y][x]->SetIsDropping(true);
					dropBlocks.push_back(blocks[y][x]);
					isDropCheck = true;
				}
				else if (x != cols - 1 && blocks[y - 1][x + 1] && blocks[y - 1][x + 1]->GetCanMove())
				{
					blocks[y][x] = blocks[y - 1][x + 1];
					blocks[y - 1][x + 1] = nullptr;
					blocks[y][x]->SetMoveDir({ -1.f,1.f });
					blocks[y][x]->SetBoardPos({ x,y });
					blocks[y][x]->SetIsDropping(true);
					dropBlocks.push_back(blocks[y][x]);
					isDropCheck = true;
				}
				else if (x != 0 && blocks[y - 1][x - 1] && blocks[y - 1][x - 1]->GetCanMove())
				{
					blocks[y][x] = blocks[y - 1][x - 1];
					blocks[y - 1][x - 1] = nullptr;
					blocks[y][x]->SetMoveDir({ 1.f,1.f });
					blocks[y][x]->SetBoardPos({ x,y });
					blocks[y][x]->SetIsDropping(true);
					dropBlocks.push_back(blocks[y][x]);
					isDropCheck = true;
				}
				else if (y != rows - 1 && x != cols - 1 && !blocks[y + 1][x]  && blocks[y][x + 1] && blocks[y][x + 1]->GetCanMove() && !(blocks[y][x+1]->GetIsDropping()))
				{
					blocks[y + 1][x] = blocks[y][x + 1];
					blocks[y][x + 1] = nullptr;
					blocks[y + 1][x]->SetMoveDir({ -1.f, 1.f });
					blocks[y + 1][x]->SetBoardPos({ x,y + 1 });
					blocks[y + 1][x]->SetIsDropping(true);
					dropBlocks.push_back(blocks[y + 1][x]);
					isDropCheck = true;
				}
				else if (y != rows - 1 && x != 0 && !blocks[y + 1][x] && blocks[y][x - 1] && blocks[y][x - 1]->GetCanMove() && !(blocks[y][x - 1]->GetIsDropping()))
				{
					blocks[y + 1][x] = blocks[y][x - 1];
					blocks[y][x - 1] = nullptr;
					blocks[y + 1][x]->SetMoveDir({ 1.f, 1.f });
					blocks[y + 1][x]->SetBoardPos({ x,y + 1 });
					blocks[y + 1][x]->SetIsDropping(true);
					dropBlocks.push_back(blocks[y + 1][x]);
					isDropCheck = true;
				}
			}
			else if (!blocks[y][x] && !blocks[y - 1][x])
			{
				if (y != rows - 1 && x != cols - 1 && !blocks[y + 1][x] && blocks[y][x + 1] && blocks[y][x + 1]->GetCanMove() && !(blocks[y][x + 1]->GetIsDropping()))
				{
					blocks[y + 1][x] = blocks[y][x + 1];
					blocks[y][x + 1] = nullptr;
					blocks[y + 1][x]->SetMoveDir({ -1.f, 1.f });
					blocks[y + 1][x]->SetBoardPos({ x,y + 1 });
					blocks[y + 1][x]->SetIsDropping(true);
					dropBlocks.push_back(blocks[y + 1][x]);
					isDropCheck = true;
				}
				else if (y != rows - 1 && x != 0 && !blocks[y + 1][x]  && blocks[y][x - 1] && blocks[y][x - 1]->GetCanMove() && !(blocks[y][x - 1]->GetIsDropping()))
				{
					blocks[y + 1][x] = blocks[y][x - 1];
					blocks[y][x - 1] = nullptr;
					blocks[y + 1][x]->SetMoveDir({ 1.f, 1.f });
					blocks[y + 1][x]->SetBoardPos({ x,y + 1 });
					blocks[y + 1][x]->SetIsDropping(true);
					dropBlocks.push_back(blocks[y + 1][x]);
					isDropCheck = true;
				}
			}
		}
	}

	// 맨윗 줄 검사할 때
	int y = 0;
	for (int x = cols - 1; x >= 0; --x)
	{
		if (!blocks[y][x])
		{
			blocks[y][x] = blockPool.back();
			blockPool.pop_back();
			blocks[y][x]->Reset();
			blocks[y][x]->SetBlockType((BlockTypes)Utils::RandomRange(2, 6));
			blocks[y][x]->SetBoardPos({ x,y });
			blocks[y][x]->SetPosition({ boardLeft + (float)Block::SIZE * x, boardTop - (float)Block::SIZE });
			blocks[y][x]->SetMoveDir({ 0.f,1.f });
			blocks[y][x]->SetIsDropping(true);
			dropBlocks.push_back(blocks[y][x]);
			isDropCheck = true;
		}
	}	

	if (isDropCheck)
		nextState = GameState::Drop;
	else
		nextState = GameState::MatchCheck;

	isDropping = true;
	currentState = GameState::Animation;
}

void Board::Init()
{
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			blocks[y][x] = new Block();
			blocks[y][x]->Init();

			tiles[y][x] = new Tile();
			tiles[y][x]->Init();

			Block* block = new Block();
			block->Init();
			blockPool.push_back(block);
		}
	}
}

void Board::Release()
{
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			blocks[y][x]->Release();
			tiles[y][x]->Release();
		}
	}
}

void Board::Reset()
{
	scene = (SceneGame*)SCENE_MGR.GetCurrentScene();

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			if (!blocks[y][x])
			{
				blocks[y][x] = blockPool.back();
				blocks[y][x]->Reset();
				blockPool.pop_back();
			}
			else
			{
				blocks[y][x]->Reset();
			}

			tiles[y][x]->Reset();
		}
	}
	paintedCount = 0;
	maxPaintableCount = 0;

	SetBoardBlock(initialBlockState);
	SetBoardTile(initialTileState);
}

void Board::Update(float dt)
{
	if (scene->isPlaying)
	{
		switch (currentState)
		{
			case GameState::Idle:
				Idle();
				break;
			case GameState::Swap:
				SwapBlock();
				break;
			case GameState::Animation:
				Animation(dt);
				break;
			case GameState::MatchCheck:
				CheckMatchAll();
				break;
			case GameState::Remove:
				RemoveBlocks();
				break;
			case GameState::Drop:
				DropBlocks();
				break;
		}

		for (int y = 0; y < rows; y++)
		{
			for (int x = 0; x < cols; x++)
			{
				if (!blocks[y][x])
					continue;

				blocks[y][x]->Update(dt);
			}
		}
	}
}

void Board::Draw(sf::RenderWindow& window)
{
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			tiles[y][x]->Draw(window);

			if (!blocks[y][x])
				continue;

			blocks[y][x]->Draw(window);
		}
	}
}

void Board::StageTargetUIUpdate()
{
	for (auto wall : destroyedWalls)
	{
		scene->remainWallCount--;
		wall->SetBlockType(BlockTypes::None);
	}
	destroyedWalls.clear();

	scene->remainTileCount = maxPaintableCount - paintedCount;
	((StageUI*)scene->FindGameObject("UI"))->UpdateTarget();
}

void Board::RemoveBlocksUpdate()
{
	for (auto block : removeBlocks)
	{
		block->SetActive(false);
		block->SetIsRemoving(false);
		blockPool.push_back(block);
		blocks[block->GetBoardPos().y][block->GetBoardPos().x] = nullptr;
	}
	removeBlocks.clear();

	for (auto block : nextRemoveBlocks)
	{
		removeBlocks.insert(block);
	}
	nextRemoveBlocks.clear();
}

void Board::RelocateBoard()
{
	scene->isRelocate = true;

	BlockTypes blockType;
	BlockTypes temp;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			if (!blocks[y][x])
				continue;

			blockType = blocks[y][x]->GetBlockType();

			if (blockType == BlockTypes::None || blockType == BlockTypes::Wall)
				continue;

			do
			{
				blocks[y][x]->SetBlockType((BlockTypes)Utils::RandomRange(2, 6));
				temp = blocks[y][x]->GetBlockType();
			} while (
				(x >= 2 && blocks[y][x-2] && blocks[y][x - 2]->GetBlockType() == temp && blocks[y][x - 1] && blocks[y][x - 1]->GetBlockType() == temp) ||
				(y >= 2 && blocks[y-2][x] && blocks[y - 2][x]->GetBlockType() == temp && blocks[y-1][x] && blocks[y - 1][x]->GetBlockType() == temp)
				);
		}
	}

	if (!CheckMatchPossible())
	{
		RelocateBoard();
	}
}
