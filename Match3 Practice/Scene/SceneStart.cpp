#include "stdafx.h"
#include "SceneStart.h"

SceneStart::SceneStart()
	: Scene(SceneIds::Start)
{
}

void SceneStart::Init()
{
	Scene::Init();
}

void SceneStart::Enter()
{
	Scene::Enter();
}

void SceneStart::Update(float dt)
{
	Scene::Update(dt);
}