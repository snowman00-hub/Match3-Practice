#include "stdafx.h"
#include "Board.h"

void Board::SetBoard(int* arr)
{
	BlockTypes blockType;
	TileTypes tileType;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			blockType = (BlockTypes)arr[9 * y + x];
			tiles[y][x]->SetTileType(TileTypes::Default);
			if (blockType == BlockTypes::Jem)
			{
				blocks[y][x]->SetBlockType((BlockTypes)Utils::RandomRange(2,6));
			}
			else 
			{				
				blocks[y][x]->SetBlockType(blockType);

				if (blockType == BlockTypes::None)
				{
					blocks[y][x]->SetActive(false);
					tiles[y][x]->SetActive(false);
					tiles[y][x]->SetTileType(TileTypes::None);
				}
			}
			tiles[y][x]->SetBoardPos({ x,y });
			tiles[y][x]->SetPosition({ boardLeft + (float)Tile::SIZE * x, boardTop + (float)Tile::SIZE * y });

			blocks[y][x]->SetBoardPos({ x,y });
			blocks[y][x]->SetPosition({ boardLeft + (float)Block::SIZE * x, boardTop + (float)Block::SIZE * y });
		}
	}
}

void Board::Idle()
{
	mousePos = InputMgr::GetMousePosition();

	if (InputMgr::GetMouseButton(sf::Mouse::Left))
	{
		int x = (mousePos.x - boardLeft) / Block::SIZE;
		int y = (mousePos.y - boardTop) / Block::SIZE;

		if (!selectedBlock)
		{
			selectedBlock = blocks[y][x];
		}
		else if (selectedBlock != blocks[y][x])
		{
			targetBlock = blocks[y][x];
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
	}

	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
	{
		selectedBlock = nullptr;
	}
}

void Board::SwapBlock()
{
	bool isMatchS = CheckMatchAt(selectedBlock->GetBoardPos());
	bool isMatchT = CheckMatchAt(targetBlock->GetBoardPos());

	if (isMatchS || isMatchT)
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
			selectedBlock->SetMoveDir({ 0.f,0.f });
			selectedBlock->SetIsSwapping(false);
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

	if (isRemoving)
	{
		if (aniTimer > Block::removeDuration)
		{
			aniTimer = 0.f;

			for (auto block : blockPool)
			{
				block->SetActive(false);
				block->SetIsRemoving(false);
				blocks[block->GetBoardPos().y][block->GetBoardPos().x] = nullptr;
			}

			currentState = GameState::Idle; // Drop으로 나중에 고치기
		}
	}
}

bool Board::CheckMatchAt(sf::Vector2i pos)
{
	int x = pos.x;
	int y = pos.y;
	int matchCount = 1;
	bool isMatch = false;
	BlockTypes type = blocks[y][x]->GetBlockType();

	std::vector<sf::Vector2i> tempPos;
	tempPos.push_back(pos);

	// 가로 검사
	int nx = x;
	while (true)
	{
		nx--;
		if (nx < 0)
			break;

		if (type == blocks[y][nx]->GetBlockType())
		{
			tempPos.push_back(sf::Vector2i(nx, y));
			matchCount++;
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

		if (type == blocks[y][nx]->GetBlockType())
		{
			tempPos.push_back(sf::Vector2i(nx, y));
			matchCount++;
		}
		else
		{
			break;
		}
	}

	if (matchCount >= 3)
	{
		isMatch = true;
		for (auto pos : tempPos)
		{
			removeBlocks.insert(blocks[pos.y][pos.x]);
		}
		tempPos.clear();
	}
	else
	{
		tempPos.clear();
		tempPos.push_back(pos);
		matchCount = 1;
	}

	// 세로 검사
	int ny = y;
	while (true)
	{
		ny--;
		if (ny < 0)
			break;

		if (type == blocks[ny][x]->GetBlockType())
		{
			tempPos.push_back(sf::Vector2i(x, ny));
			matchCount++;
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

		if (type == blocks[ny][x]->GetBlockType())
		{
			tempPos.push_back(sf::Vector2i(x, ny));
			matchCount++;
		}
		else
		{
			break;
		}
	}

	if (matchCount >= 3)
	{
		isMatch = true;
		for (auto pos : tempPos)
		{
			removeBlocks.insert(blocks[pos.y][pos.x]);
		}
	}

	return isMatch;
}

bool Board::CheckMatchAll()
{
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			CheckMatchAt(sf::Vector2i(x, y));
		}
	}
	return false;
}

void Board::RemoveBlocks()
{
	for (auto block : removeBlocks)
	{
		block->SetIsRemoving(true);
		block->PlaySparkle();
		blockPool.push_back(block);
	}
	removeBlocks.clear();
	isRemoving = true;

	currentState = GameState::Animation;
	nextState = GameState::Drop;
}

void Board::DropBlocks()
{

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
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			blocks[y][x]->Reset();
			tiles[y][x]->Reset();
		}
	}
}

void Board::Update(float dt)
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
