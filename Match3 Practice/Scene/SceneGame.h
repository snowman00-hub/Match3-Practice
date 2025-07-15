#pragma once
#include "Scene.h"
#include "StageUI.h"
#include "Board.h"
#include "Tile.h"
#include "Block.h"

class Board;
class StageUI;

class SceneGame : public Scene
{
protected:
	Board* board;
	StageUI* ui;

	sf::Sprite background;
	sf::Sprite cursor;
	sf::Sprite redTile;
	sf::Sprite wall;

	int stageLevel = 1;
	int initialSwapCount;

	sf::Text relocateMessage;
	sf::Text clearMessage;
	sf::Text defeatMessage;
	float relocateTimer = 0.f;
	float gameEndTimer = 0.f;
	const float relocateTime = 3.0f;

	bool targetIsTile = false;
	bool targetIsWall = false;

public:
	bool isClear = false;
	bool isDefeat = false;
	bool isRelocate = false;

	int swapCount;
	int remainTileCount = 0;
	int remainWallCount = 0;

	SceneGame();
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};