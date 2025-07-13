#pragma once
#include "Scene.h"

class TextGo;
class StageUI;

class SceneDev1 : public Scene
{
protected:
	StageUI* ui;

public:
	SceneDev1();

	void Init() override;
	void Enter() override;
};

