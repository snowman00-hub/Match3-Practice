#pragma once
#include "SceneGame.h"
class SceneStage1 : public SceneGame
{
protected:

public:
	SceneStage1();
	~SceneStage1() override = default;

	void Init() override;
};

