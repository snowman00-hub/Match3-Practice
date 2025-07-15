#include "stdafx.h"
#include "SceneGame.h"
#include "Animator.h"
#include "SceneLobby.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

SceneGame::SceneGame(SceneIds id)
	: Scene(id)
{
}

void SceneGame::Init()
{
	initialSwapCount = 20;
	swapCount = initialSwapCount;

	background.setTexture(TEXTURE_MGR.Get("graphics/bg_sky.png"));

	ui = (StageUI*)AddGameObject(new StageUI("UI"));
	ui->SetStageLevel(stageLevel);
	ui->SetSwapCount(&swapCount);
	ui->UpdateSwapCount();
	redTile.setTexture(TEXTURE_MGR.Get("graphics/tiles.png"));
	redTile.setTextureRect(sf::IntRect(Tile::SIZE, 0, Tile::SIZE, Tile::SIZE));
	wall.setTexture(TEXTURE_MGR.Get("graphics/blocks.png"));
	wall.setTextureRect(sf::IntRect(0, 0, Block::SIZE, Block::SIZE));

	relocateMessage.setFont(FONT_MGR.Get("fonts/Maplestory Light.ttf"));
	relocateMessage.setCharacterSize(80);
	relocateMessage.setFillColor(sf::Color::Yellow);
	relocateMessage.setString(L"재배치!");
	Utils::SetOrigin(relocateMessage, Origins::MC);
	relocateMessage.setPosition({ 600.f,150.f });

	clearMessage.setFont(FONT_MGR.Get("fonts/Maplestory Light.ttf"));
	clearMessage.setCharacterSize(80);
	clearMessage.setFillColor(sf::Color::Yellow);
	clearMessage.setString("Clear!");
	Utils::SetOrigin(clearMessage, Origins::MC);
	clearMessage.setPosition({ 360.f,380.f });

	defeatMessage.setFont(FONT_MGR.Get("fonts/Maplestory Light.ttf"));
	defeatMessage.setCharacterSize(80);
	defeatMessage.setFillColor(sf::Color::Blue);
	defeatMessage.setString("Defeat");
	Utils::SetOrigin(defeatMessage, Origins::MC);
	defeatMessage.setPosition({ 360.f,380.f });

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
		0,0,1,0,1,0,0,0,0,
		0,0,0,1,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
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
	board->SetInitialTileState(initialTileState);

	Scene::Init();

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

	isClear = false;
	isDefeat = false;
	gameEndTimer = 0.f;

	swapCount = initialSwapCount;
	ui->UpdateSwapCount();
	ui->UpdateTarget();

	cursor.setTexture(TEXTURE_MGR.Get("graphics/cursor.png"));
	Utils::SetOrigin(cursor, Origins::TL);
}

void SceneGame::Exit()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
	remainWallCount = 0;

	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));

	if (isClear)
	{
		gameEndTimer += dt;
		if (gameEndTimer > 3.0f)
		{
			gameEndTimer = 0.f;
			SceneLobby::nextStageLevel++;
			SCENE_MGR.ChangeScene(SceneIds::Lobby);
		}
	}
	else if (isDefeat)
	{
		gameEndTimer += dt;
		if (gameEndTimer > 3.0f)
		{
			gameEndTimer = 0.f;
			SCENE_MGR.ChangeScene(SceneIds::Lobby);
		}
	}

	if (isRelocate)
	{
		relocateTimer += dt;
		if (relocateTimer > relocateTime)
		{
			isRelocate = false;
			relocateTimer = 0.f;
		}
	}

	if(!isDefeat && !isClear)
		Scene::Update(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	Scene::Draw(window);
	window.setView(uiView);
	if (isRelocate)
		window.draw(relocateMessage);
	if (isClear)
		window.draw(clearMessage);
	if (isDefeat)
		window.draw(defeatMessage);
	window.draw(cursor);
}
