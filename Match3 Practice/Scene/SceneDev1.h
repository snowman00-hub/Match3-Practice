#pragma once
#include "Scene.h"

class TextGo;
class StageUI;

class SceneDev1 : public Scene
{
protected:
	StageUI* ui;

	sf::Sprite redTile;
	sf::Sprite wall;

public:
	SceneDev1();

	void Init() override;
	void Enter() override;
};

