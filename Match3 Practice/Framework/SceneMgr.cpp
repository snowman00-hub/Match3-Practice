#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneDev1.h"
#include "SceneDev2.h"
#include "SceneGame.h"
#include "SceneStart.h"
#include "SceneLobby.h"
#include "SceneStage1.h"
#include "SceneStage2.h"
#include "SceneStage3.h"

void SceneMgr::Init()
{
	scenes[SceneIds::Start] = new SceneStart();
	scenes[SceneIds::Lobby] = new SceneLobby();
	scenes[SceneIds::Stage1] = new SceneStage1();
	scenes[SceneIds::Stage2] = new SceneStage2();
	scenes[SceneIds::Stage3] = new SceneStage3();
	scenes[SceneIds::Game] = new SceneGame();
	scenes[SceneIds::Dev1] = new SceneDev1();
	scenes[SceneIds::Dev2] = new SceneDev2();

	for (auto pair : scenes)
	{
		pair.second->Init();
	}

	currentScene = startScene;
	scenes[currentScene]->Enter();
}

void SceneMgr::Release()
{
	for (auto pair : scenes)
	{
		if (pair.second->Id == currentScene)
		{
			pair.second->Exit();
		}
		pair.second->Release();
		delete pair.second;
	}
	scenes.clear();
}

void SceneMgr::ChangeScene(SceneIds id)
{
	nextScene = id;
}

void SceneMgr::Update(float dt)
{
	if (nextScene != SceneIds::None)
	{
		scenes[currentScene]->Exit();
		currentScene = nextScene;
		nextScene = SceneIds::None;
		scenes[currentScene]->Enter();
	}

	scenes[currentScene]->Update(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	scenes[currentScene]->Draw(window);
}
