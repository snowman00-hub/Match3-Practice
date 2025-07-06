#pragma once
#include "GameObject.h"

class Board : public GameObject
{
public:
	static const int rows = 9;
	static const int cols = 9;

protected:
	Block* blocks[rows][cols];

	std::vector<sf::Vector2i> removeIndexs;

	GameState state = GameState::Idle;

public:
	Board() = default;
	~Board() override = default;

	void SetBoard(int* arr);

	void SwapBlock(sf::Vector2i Pos, sf::Vector2i destPos);
	void Animation();
	void MatchCheck();
	void RemoveBlocks();
	void DropBlocks();

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};