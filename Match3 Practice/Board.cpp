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
		selectedBlock->SetBoardPos(targetPos);
		targetBlock->SetBoardPos(selectedPos);

		selectedBlock->SetMoveDir((sf::Vector2f)(targetPos - selectedPos));
		targetBlock->SetMoveDir((sf::Vector2f)(selectedPos - targetPos));

		selectedBlock->SetIsSwapping(true);
		targetBlock->SetIsSwapping(true);
		isSwapping = true;

		currentState = GameState::Animation;
		nextState = GameState::Swap;
	}
}

void Board::SwapBlock()
{
	bool isMatchS = CheckMatchAt(selectedBlock->GetBoardPos());
	bool isMatchT = CheckMatchAt(targetBlock->GetBoardPos());

	if (isMatchS || isMatchT)
	{
		RemoveBlocks();
	}
	else
	{
		sf::Vector2i selectedPos = selectedBlock->GetBoardPos();
		sf::Vector2i targetPos = targetBlock->GetBoardPos();
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
}

bool Board::CheckMatchAt(sf::Vector2i pos)
{
	return false;
}

void Board::CheckMatchAll()
{
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			blocks[y][x];
		}
	}
}

void Board::RemoveBlocks()
{
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
			break;
		case GameState::Remove:
			break;
		case GameState::Drop:
			break;
	}	

	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
	{
	}

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
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
			blocks[y][x]->Draw(window);
		}
	}
}
