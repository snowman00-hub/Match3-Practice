#pragma once
#include "GameObject.h"

// WindowSize : 720, 960
class SceneGame;
class Block;
class Tile;

class Board : public GameObject
{
public:
	static const int rows = 9;
	static const int cols = 9;

protected:
	SceneGame* scene = nullptr;

	Block* blocks[rows][cols];
	Tile* tiles[rows][cols];

	Block* selectedBlock = nullptr;
	Block* targetBlock = nullptr;

	sf::Vector2i mousePos;

	std::unordered_set<Block*> removeBlocks;
	std::unordered_set<Block*> nextRemoveBlocks;
	std::unordered_set<Tile*> paintTiles;
	std::vector<Block*> dropBlocks;
	std::vector<Block*> blockPool;

	GameState currentState = GameState::Idle;
	GameState nextState = GameState::Idle;

	const float boardLeft = 90.f;
	const float boardTop = 210.f;

	bool isSwapping = false;
	bool isRemoving = false;
	bool isDropping = false;

	float aniTimer = 0.f;

	int paintedCount;
	int maxPaintableCount;

	int initialPaintedCount;
	int initialMaxPaintableCount;

	int* initialBlockState;
	int* initialTileState;

public:
	Board() = default;
	~Board() override = default;

	void SetInitialBlockState(int* arr) { initialBlockState = arr; }
	void SetInitialTileState(int* arr, int count, int maxCount) 
	{ 
		initialTileState = arr; 
		initialPaintedCount = count;
		initialMaxPaintableCount = maxCount;
	}
	void SetBoardBlock(int* arr);
	void SetBoardTile(int* arr, int count, int maxCount);

	int GetRemainPaintableCount() { return maxPaintableCount - paintedCount; }

	void Idle();
	void SwapBlock();
	void Animation(float dt);
	bool CheckMatchAt(sf::Vector2i pos);
	void CheckMatchAll();
	void CheckObstacleNeighbors(sf::Vector2i pos);
	void CheckSpecialBlockRemoved();
	void RemoveBlocks();
	void DropBlocks();

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};