#include "stdafx.h"
#include "StageUI.h"

StageUI::StageUI(const std::string& name)
	: GameObject(name)
{
}

void StageUI::Init()
{
	sortingLayer = SortingLayers::UI;

	backgroundPanel.setTexture(TEXTURE_MGR.Get("graphics/backgroundPanel.png"));
	swapCountPanel.setTexture(TEXTURE_MGR.Get("graphics/swapCountPanel.png"));
	targetCountPanel.setTexture(TEXTURE_MGR.Get("graphics/targetCountPanel.png"));
	stageLevelPanel.setTexture(TEXTURE_MGR.Get("graphics/stageLevelPanel.png"));

	swapCountText.setFont(FONT_MGR.Get("fonts/Maplestory Light.ttf"));
	stageLevel.setFont(FONT_MGR.Get("fonts/Maplestory Light.ttf")); 

	backgroundPanel.setPosition({ startX,startY });
	swapCountPanel.setPosition({ startX + 30.f,startY + 30.f });
	targetCountPanel.setPosition({ startX + 150.f,startY + 30.f });
	stageLevelPanel.setPosition({ startX + 225.f,startY + 15.f });

	stageLevel.setCharacterSize(20.f);
	stageLevel.setFillColor(sf::Color::Black);
	Utils::SetOrigin(stageLevel, Origins::TC);
	stageLevel.setPosition(stageLevelPanel.getPosition() + sf::Vector2f(75.f, 5.f));

	swapCountText.setCharacterSize(60.f);
	swapCountText.setFillColor(sf::Color::Black);
	Utils::SetOrigin(swapCountText, Origins::TC);
	swapCountText.setPosition(swapCountPanel.getPosition() + sf::Vector2f(50.f, 10.f));
}

void StageUI::Release()
{
}

void StageUI::Reset()
{
}

void StageUI::Update(float dt)
{
}

void StageUI::Draw(sf::RenderWindow& window)
{
	window.draw(backgroundPanel);
	window.draw(swapCountPanel);
	window.draw(swapCountText);
	window.draw(targetCountPanel);
	window.draw(stageLevelPanel);
	window.draw(stageLevel);
	for (auto& target : targets)
	{
		window.draw(*target.sprite);
		window.draw(target.countText);
	}
}

void StageUI::SetStageLevel(int level)
{
	stageLevel.setString("Stage " + std::to_string(level));
	Utils::SetOrigin(stageLevel, Origins::TC);
}

void StageUI::SetTarget(sf::Sprite* sprite, int* count)
{
	if (*count == 0)
		return;

	sf::Text countText;
	countText.setFont(FONT_MGR.Get("fonts/Maplestory Light.ttf"));
	countText.setCharacterSize(20.f);
	countText.setFillColor(sf::Color::Black);
	countText.setString(std::to_string(*count));
	Utils::SetOrigin(countText, Origins::TC);

	sprite->setScale({ 0.75f,0.75f });
	targets.push_back({ sprite, countText,count });
	
	int size = targets.size();
	switch (size)
	{
		case 1:
			targets[0].sprite->setPosition(stageLevelPanel.getPosition() + sf::Vector2f(50.f, 45.f));
			targets[0].countText.setPosition(stageLevelPanel.getPosition() + sf::Vector2f(72.5f, 87.f));
			break;
		case 2:
			targets[0].sprite->setPosition(stageLevelPanel.getPosition() + sf::Vector2f(0.f, 45.f));
			targets[0].countText.setPosition(stageLevelPanel.getPosition() + sf::Vector2f(22.5f, 87.f));
			targets[1].sprite->setPosition(stageLevelPanel.getPosition() + sf::Vector2f(100.f, 45.f));
			targets[1].countText.setPosition(stageLevelPanel.getPosition() + sf::Vector2f(122.5f, 87.f));
			break;
		case 3:
			break;
	}
}

void StageUI::UpdateTarget()
{
	for (auto& target : targets)
	{
		target.countText.setString(std::to_string(*target.count));
		Utils::SetOrigin(target.countText, Origins::TC);
	}
}

void StageUI::UpdateSwapCount()
{
	if (*swapCount >= 10)
	{
		swapCountText.setString(std::to_string(*swapCount));
	}
	else
	{
		swapCountText.setString("0" + std::to_string(*swapCount));
	}
	Utils::SetOrigin(swapCountText, Origins::TC);
}
