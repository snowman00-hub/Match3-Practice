#pragma once
#include "Scene.h"
class SceneLobby : public Scene
{
protected:
	sf::Sprite background;
	sf::Sprite cursor;

	sf::Sprite nextStageButton;
	sf::Text ButtonMessage;

public:
	static int nextStageLevel;

	SceneLobby();
	~SceneLobby() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};