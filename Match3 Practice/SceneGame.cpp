#include "stdafx.h"
#include "SceneGame.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	board = (Board*)AddGameObject(new Board());
	int initialState[81] = 
	{
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0
	};
	test = (SpriteGo*)AddGameObject(new SpriteGo("graphics/Blocks.png"));

	Scene::Init();

	board->SetBoard(initialState);
}

void SceneGame::Enter()
{
	Scene::Enter();
	//Utils::SetSpriteSize(test->GetSprite(), 60.f, 60.f);
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
}