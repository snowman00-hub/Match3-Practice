#include "stdafx.h"
#include "SceneLobby.h"

int SceneLobby::nextStageLevel = 1;

SceneLobby::SceneLobby()
	: Scene(SceneIds::Lobby)
{
}

void SceneLobby::Init()
{
	background.setTexture(TEXTURE_MGR.Get("graphics/bg_sky.png"));

	nextStageButton.setTexture(TEXTURE_MGR.Get("graphics/button.png"));
	nextStageButton.setPosition({ 360.f,750.f });
	Utils::SetOrigin(nextStageButton, Origins::MC);

	ButtonMessage.setFont(FONT_MGR.Get("fonts/Maplestory Light.ttf"));
	ButtonMessage.setCharacterSize(50);
	ButtonMessage.setFillColor(sf::Color::Magenta);
	ButtonMessage.setPosition(nextStageButton.getPosition() + sf::Vector2f(0.f,-10.f));
	ButtonMessage.setString("Stage " + std::to_string(nextStageLevel));
	Utils::SetOrigin(ButtonMessage, Origins::MC);

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

	ButtonMessage.setString("Stage " + std::to_string(nextStageLevel));
	Utils::SetOrigin(ButtonMessage, Origins::MC);

	Scene::Enter();

	cursor.setTexture(TEXTURE_MGR.Get("graphics/cursor.png"));
	Utils::SetOrigin(cursor, Origins::TL);
}

void SceneLobby::Update(float dt)
{
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		if (nextStageButton.getGlobalBounds().contains(cursor.getPosition()))
		{
			SOUND_MGR.PlaySfx("sound/click.mp3");
			SCENE_MGR.ChangeScene((SceneIds)(nextStageLevel + 1));
		}
	}

	Scene::Update(dt);
}

void SceneLobby::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	Scene::Draw(window);
	window.draw(nextStageButton);
	window.draw(ButtonMessage);
	window.draw(cursor);
}