#pragma once
#include "GameObject.h"

// WindowSize : 720, 960

class Board : public GameObject
{
public:
	static const int rows = 9;
	static const int cols = 9;

protected:
	Block* blocks[rows][cols];
	Tile* tiles[rows][cols];

	Block* selectedBlock = nullptr;
	Block* targetBlock = nullptr;

	sf::Vector2i mousePos;

	std::unordered_set<Block*> removeBlocks;
	std::vector<Block*> dropBlocks;
	std::vector<Block*> blockPool;

	GameState currentState = GameState::Idle;
	GameState nextState = GameState::Idle;

	const float boardLeft = 90.f;
	const float boardTop = 150.f;

	bool isSwapping = false;
	bool isRemoving = false;
	bool isDropping = false;

	float aniTimer = 0.f;

public:
	Board() = default;
	~Board() override = default;

	void SetBoard(int* arr);

	void Idle();
	void SwapBlock();
	void Animation(float dt);
	bool CheckMatchAt(sf::Vector2i pos);
	void CheckMatchAll();
	void RemoveBlocks();
	void DropBlocks();

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};