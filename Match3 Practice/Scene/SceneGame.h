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

	int stageLevel = 1;

	sf::Sprite redTile;
	sf::Sprite wall;

public:
	bool isClear = false;
	bool isDefeat = false;

	int swapCount = 20;
	int remainTileCount;
	int remainWallCount;

	SceneGame();
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void StageClear();
	void StageDefeat();
};