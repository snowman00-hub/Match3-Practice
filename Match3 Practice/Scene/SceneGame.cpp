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
	relocateMessage.setString(L"Àç¹èÄ¡!");
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

	//
	optionButton = (Button*)AddGameObject(new Button());
	optionButton->SetPosition({ 580.f,90.f });
	optionButton->sprite.setTexture(TEXTURE_MGR.Get("graphics/option.png"));
	optionButton->SetCallBack([this]()
		{
			if (board->GetCurrentState() == GameState::Idle)
			{
				if (optionUI->GetActive())
				{
					isPlaying = true;
					optionUI->SetActive(false);
					SOUND_MGR.PlaySfx("sound/click.mp3");
				}
				else
				{
					isPlaying = false;
					optionUI->SetActive(true);
					SOUND_MGR.PlaySfx("sound/click.mp3");
				}
			}
		}
	);

	optionUI = (OptionUI*)AddGameObject(new OptionUI());
	optionUI->SetActive(false);
	optionUI->SetPosition({ 245.f,280.f });

	skillButton = (Button*)AddGameObject(new Button());
	skillButton->SetPosition({ 580.f,860.f });
	skillButton->sprite.setTexture(TEXTURE_MGR.Get("graphics/star.png"));
	skillButton->SetCallBack([this]()
		{
			if (board->GetCurrentState() == GameState::Idle)
			{
				board->RelocateBoard();
				skillButton->SetActive(false);
				SOUND_MGR.PlaySfx("sound/click.mp3");
			}
		}
	);
	//

	Scene::Init();

	if (targetIsTile)
	{
		remainTileCount++;
		ui->SetTarget(&redTile, &remainTileCount);
		remainTileCount--;
	}

	if (targetIsWall)
	{
		remainWallCount++;
		ui->SetTarget(&wall, &remainWallCount);
		remainWallCount--;
	}
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

	isPlaying = true;
	isClear = false;
	isDefeat = false;
	gameEndTimer = 0.f;

	swapCount = initialSwapCount;
	ui->UpdateSwapCount();
	ui->UpdateTarget();

	cursor.setTexture(TEXTURE_MGR.Get("graphics/cursor.png"));
	Utils::SetOrigin(cursor, Origins::TL);

	skillButton->SetActive(true);
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
