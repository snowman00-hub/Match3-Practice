#pragma once
#include "Scene.h"
class SceneStart : public Scene
{
protected:

public:
	SceneStart();
	~SceneStart() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
};

