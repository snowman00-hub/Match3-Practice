#pragma once
#include "GameObject.h"

struct Option
{
	sf::Sprite optionPanel;
	Button bgmButton;
	Button sfxButton;
};

class OptionUI : public GameObject
{
protected:
	Option UI;

public:
	OptionUI(const std::string& name = "");
	virtual ~OptionUI() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

