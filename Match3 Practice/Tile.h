#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
protected:
	sf::Sprite tile;
	std::string tileTexId = "graphics/tiles.png";

	TileTypes type = TileTypes::Default;

	sf::Vector2i boardPos;

public:
	static const int SIZE = 60;

	Tile() = default;
	virtual ~Tile() = default;

	void SetTileType(TileTypes type);
	void SetBoardPos(sf::Vector2i pos) { boardPos = pos; }

	TileTypes GetTileType() const { return type; }

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

