#include "stdafx.h"
#include "SceneStart.h"

SceneStart::SceneStart()
	: Scene(SceneIds::Start)
{
}

void SceneStart::Init()
{
	background.setTexture(TEXTURE_MGR.Get("graphics/bg_sky.png"));

	startMessage.setFont(FONT_MGR.Get("fonts/Maplestory Light.ttf"));
	startMessage.setCharacterSize(100);
	startMessage.setFillColor(sf::Color::Yellow);
	startMessage.setString("Start Game!");
	Utils::SetOrigin(startMessage, Origins::MC);
	startMessage.setPosition({ 360.f, 400.f });

	Scene::Init();
}

void SceneStart::Enter()
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

void SceneStart::Update(float dt)
{
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		SCENE_MGR.ChangeScene(SceneIds::Lobby);
	}

	Scene::Update(dt);
}

void SceneStart::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(startMessage);
	Scene::Draw(window);
	window.draw(cursor);
}