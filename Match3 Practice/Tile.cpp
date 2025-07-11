#include "stdafx.h"
#include "Tile.h"

void Tile::SetTileType(TileTypes type)
{
	this->type = type;
	if (type != TileTypes::None)
	{
		tile.setTextureRect(sf::IntRect(((int)type) * SIZE, 0, SIZE, SIZE));
	}
}

void Tile::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	tile.setPosition(pos);
}

void Tile::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	tile.setRotation(rot);
}

void Tile::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	tile.setScale(s);
}

void Tile::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	tile.setOrigin(o);
}

void Tile::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(tile, preset);
	}
}

void Tile::Init()
{
	tile.setTexture(TEXTURE_MGR.Get(tileTexId));
	sortingLayer = SortingLayers::Background;
	sortingOrder = 1;
}

void Tile::Release()
{
}

void Tile::Reset()
{
}

void Tile::Update(float dt)
{
}

void Tile::Draw(sf::RenderWindow& window)
{
	if (type != TileTypes::None)
		window.draw(tile);
}