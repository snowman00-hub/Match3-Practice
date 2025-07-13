#include "stdafx.h"
#include "SceneDev1.h"
#include "TextGo.h"
#include "StageUI.h"

SceneDev1::SceneDev1()
	: Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	ui = (StageUI*)AddGameObject(new StageUI("UI"));
	ui->SetStageLevel(1);
	ui->SetSwapCount(20);

	Scene::Init();
}

void SceneDev1::Enter()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	Scene::Enter();
}