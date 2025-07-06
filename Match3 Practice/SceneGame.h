#pragma once
#include "Scene.h"

class SceneGame : public Scene
{
protected:
	Board* board;
	SpriteGo* test;

public:
	SceneGame();
	~SceneGame() override;

	void Init() override;

	void Enter() override;

	void Update(float dt) override;
};

