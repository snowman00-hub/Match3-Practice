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
		}
	}
}

void Board::Release()
{
}

void Board::Reset()
{
}

void Board::Update(float dt)
{
}

void Board::Draw(sf::RenderWindow& window)
{

}
