#pragma once
#include "SceneGame.h"

class SceneDev1 : public SceneGame
{
protected:

public:
	SceneDev1();
	~SceneDev1() override = default;

	void Init() override;
};

