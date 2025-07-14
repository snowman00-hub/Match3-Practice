#pragma once
#include "Scene.h"

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

	sf::Text relocateMessage;
	float relocateTimer = 0.f;
	const float relocateTime = 3.0f;

public:
	bool isClear = false;
	bool isDefeat = false;
	bool isRelocate = false;

	int swapCount = 20;
	int remainTileCount = 0;
	int remainWallCount = 0;

	SceneGame();
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};