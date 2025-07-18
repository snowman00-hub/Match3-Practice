#pragma once
#include "Scene.h"

class SceneStart : public Scene
{
protected:
	sf::Sprite background;
	sf::Sprite cursor;
	sf::Text startMessage;

public:
	SceneStart();
	~SceneStart() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

