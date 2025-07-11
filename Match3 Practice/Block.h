#pragma once
#include "GameObject.h"

class Block : public GameObject
{
public:
	static const int SIZE = 60;
	static const float moveDuration;

protected:
	sf::Sprite block;

	sf::Vector2i boardPos;
	sf::Vector2f moveDir = { 0.f,0.f };
	float moveSpeed = SIZE / moveDuration;

	BlockTypes type = BlockTypes::None;

	std::string blockTexId = "graphics/blocks.png";

	bool isMoving = false;

public:
	Block() = default;
	~Block() override = default;

	void SetBlockType(BlockTypes type);
	void SetBoardPos(sf::Vector2i pos) { boardPos = pos; }
	void SetMoveDir(sf::Vector2f dir) { moveDir = dir; }
	void SetIsMoving(bool b) { isMoving = b; }

	BlockTypes GetBlockType() const { return type; }
	sf::Vector2i GetBoardPos() const { return boardPos; }

	void SetPosition(const sf::Vector2f& pos) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};