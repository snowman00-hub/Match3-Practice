#pragma once
#include "Scene.h"
class SceneLobby : public Scene
{
protected:

public:
	SceneLobby();
	~SceneLobby() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
};

