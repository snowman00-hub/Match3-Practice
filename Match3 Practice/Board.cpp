#include "stdafx.h"
#include "Board.h"

void Board::SetBoard(int* arr)
{
	BlockTypes type;
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			type = (BlockTypes)arr[9 * y + x];
			if (type == BlockTypes::Jem)
			{
				blocks[y][x]->SetBlockType((BlockTypes)Utils::RandomRange(2,6));
			}
			else 
			{				
				blocks[y][x]->SetBlockType(type);

				if (type == BlockTypes::None)
					blocks[y][x]->SetActive(false);
			}
			blocks[y][x]->SetBoardPos({ x,y });
			blocks[y][x]->SetPosition({ 90.f + (float)Block::SIZE * x, (float)Block::SIZE * y });
		}
	}
}

void Board::SwapBlock(sf::Vector2i Pos, sf::Vector2i destPos)
{
}

void Board::Animation()
{
}

void Board::MatchCheck()
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
		}
	}
}

void Board::Update(float dt)
{
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
			blocks[y][x]->Draw(window);
		}
	}
}
