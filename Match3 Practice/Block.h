#pragma once
#include "GameObject.h"
#include "Animator.h"

class Block : public GameObject
{
public:
	static const int SIZE = 60;
	static const float moveDuration;
	static const float swapDuration;
	static const float removeDuration;

protected:
	sf::Sprite block;
	Animator animator;

	sf::Vector2i boardPos;
	sf::Vector2f moveDir = { 0.f,0.f };
	float moveSpeed = SIZE / moveDuration;
	float swapSpeed = SIZE / swapDuration;

	BlockTypes type = BlockTypes::None;

	std::string blockTexId = "graphics/blocks.png";

	bool isMoving = false;
	bool isSwapping = false;
	bool isRemoving = false;

public:
	Block() = default;
	~Block() override = default;

	void SetBlockType(BlockTypes type);
	void SetBoardPos(sf::Vector2i pos) { boardPos = pos; }
	void SetMoveDir(sf::Vector2f dir) { moveDir = dir; }
	void SetIsMoving(bool b) { isMoving = b; }
	void SetIsSwapping(bool b) { isSwapping = b; }
	void SetIsRemoving(bool b) { isRemoving = b; }

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

	void PlaySparkle() { animator.Play("animations/sparkle.csv"); }
};