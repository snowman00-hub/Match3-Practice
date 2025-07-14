#pragma once
#include "Scene.h"
class SceneLobby : public Scene
{
protected:
	sf::Sprite background;
	sf::Sprite cursor;

public:
	SceneLobby();
	~SceneLobby() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};