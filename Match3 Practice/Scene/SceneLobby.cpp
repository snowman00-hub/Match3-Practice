#include "stdafx.h"
#include "SceneLobby.h"

SceneLobby::SceneLobby()
	: Scene(SceneIds::Lobby)
{
}


void SceneLobby::Init()
{
	background.setTexture(TEXTURE_MGR.Get("graphics/bg_sky.png"));

	Scene::Init();
}

void SceneLobby::Enter()
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

void SceneLobby::Update(float dt)
{
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{

	}

	Scene::Update(dt);
}

void SceneLobby::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	Scene::Draw(window);
	window.draw(cursor);
}