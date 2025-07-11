#include "stdafx.h"
#include "Block.h"

const float Block::moveDuration = 0.15f;
const float Block::swapDuration = 0.1f;

void Block::SetBlockType(BlockTypes type)
{
	this->type = type;
	if (type != BlockTypes::None)
	{
		block.setTextureRect(sf::IntRect(((int)type - 1) * SIZE, 0, SIZE, SIZE));
	}
}

void Block::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	block.setPosition(pos);
}

void Block::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	block.setOrigin(o);
}

void Block::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	Utils::SetOrigin(block, preset);
}

void Block::Init()
{
	block.setTexture(TEXTURE_MGR.Get(blockTexId));
	sortingLayer = SortingLayers::Foreground;
}

void Block::Release()
{
}

void Block::Reset()
{
}

void Block::Update(float dt)
{
	if (isMoving)
	{
		sf::Vector2f pos = GetPosition();
		pos += moveDir * moveSpeed * dt;
		SetPosition(pos);
	}

	if (isSwapping)
	{
		sf::Vector2f pos = GetPosition();
		pos += moveDir * swapSpeed * dt;
		SetPosition(pos);
	}
}

void Block::Draw(sf::RenderWindow& window)
{
	if(type != BlockTypes::None)
		window.draw(block);
}
