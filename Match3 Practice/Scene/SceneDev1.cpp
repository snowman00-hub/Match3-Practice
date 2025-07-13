#include "stdafx.h"
#include "SceneDev1.h"
#include "TextGo.h"
#include "StageUI.h"
#include "Tile.h"
#include "Block.h"

SceneDev1::SceneDev1()
	: Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	ui = (StageUI*)AddGameObject(new StageUI("UI"));
	ui->SetStageLevel(1);

	redTile.setTexture(TEXTURE_MGR.Get("graphics/tiles.png"));
	redTile.setTextureRect(sf::IntRect(Tile::SIZE, 0, Tile::SIZE, Tile::SIZE));
	wall.setTexture(TEXTURE_MGR.Get("graphics/blocks.png"));
	wall.setTextureRect(sf::IntRect(0, 0, Block::SIZE, Block::SIZE));

	Scene::Init();

	redTileCount = 20;
	wallCount = 10;

	ui->SetTarget(&redTile, &redTileCount);
	ui->SetTarget(&wall, &wallCount);
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