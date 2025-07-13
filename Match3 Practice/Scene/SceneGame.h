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

public:
	SceneGame();
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};