#pragma once
#include "Scene.h"

class SceneGame : public Scene
{
protected:
	Board* board;

	sf::Sprite cursor;

public:
	SceneGame();
	~SceneGame() override;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};