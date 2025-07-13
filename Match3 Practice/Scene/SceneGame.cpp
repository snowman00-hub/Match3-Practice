#include "stdafx.h"
#include "SceneGame.h"
#include "Animator.h"
#include "Board.h"
#include "StageUI.h"
#include "Tile.h"
#include "Block.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	background.setTexture(TEXTURE_MGR.Get("graphics/bg_sky.png"));

	ui = (StageUI*)AddGameObject(new StageUI("UI"));
	ui->SetStageLevel(stageLevel);
	ui->SetSwapCount(&swapCount);
	ui->UpdateSwapCount();
	redTile.setTexture(TEXTURE_MGR.Get("graphics/tiles.png"));
	redTile.setTextureRect(sf::IntRect(Tile::SIZE, 0, Tile::SIZE, Tile::SIZE));
	wall.setTexture(TEXTURE_MGR.Get("graphics/blocks.png"));
	wall.setTextureRect(sf::IntRect(0, 0, Block::SIZE, Block::SIZE));

	board = (Board*)AddGameObject(new Board());
	// -1 빈 공간
	//  0 보석
	//  1 장애물
	static int initialBlockState[81] = 
	{
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,0,0,
		0,0,0,1,0,0,0,0,0,
		0,0,0,1,0,0,0,0,0,
		0,0,0,1,0,0,0,0,0,
		0,0,0,1,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0
	};
	
	// -1 빈 공간
	//  0 디폴트
	//  1 페인트된
	static int initialTileState[81] =
	{
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,1,0,0,0,0,0,0,0,
		0,1,0,0,0,0,0,0,0,
		0,1,0,0,0,0,0,0,0,
		0,1,0,0,0,0,0,0,0,
		0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0
	};

	board->SetInitialBlockState(initialBlockState);
	board->SetInitialTileState(initialTileState, 5, 81);

	Scene::Init();

	remainTileCount = 76;
	remainWallCount = 5;
	ui->SetTarget(&redTile, &remainTileCount);
	ui->SetTarget(&wall, &remainWallCount);
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	Scene::Enter();

	cursor.setTexture(TEXTURE_MGR.Get("graphics/cursor.png"));
	Utils::SetOrigin(cursor, Origins::TL);
}

void SceneGame::Exit()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);

	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));

	if (isClear)
	{
		std::cout << "Clear" << std::endl;
	}
	else if (isDefeat)
	{
		std::cout << "Defeat" << std::endl;
	}

	Scene::Update(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	Scene::Draw(window);
	window.setView(uiView);
	window.draw(cursor);
}