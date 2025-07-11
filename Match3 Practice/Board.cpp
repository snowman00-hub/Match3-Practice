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
