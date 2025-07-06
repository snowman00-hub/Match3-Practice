#pragma once
#include "GameObject.h"

class Block : public GameObject
{
protected:
	sf::Sprite panel;
	sf::Sprite block;

	sf::Vector2i boardPos;
	float moveSpeed = 50.f;

	BlockTypes type = BlockTypes::None;

	std::string blockTexId = "graphics/blocks.png";

public:
	static const int SIZE = 60;

	Block() = default;
	~Block() override = default;

	void SetBlockType(BlockTypes type);
	void SetBoardPos(sf::Vector2i pos) { boardPos = pos; }

	void SetPosition(const sf::Vector2f& pos) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};