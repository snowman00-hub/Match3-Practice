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
	// -1 빈 공간
	//  0 보석
	//  1 장애물
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
	
	Scene::Init();

	board->SetBoard(initialState);
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

	Scene::Update(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(uiView);
	window.draw(cursor);
}