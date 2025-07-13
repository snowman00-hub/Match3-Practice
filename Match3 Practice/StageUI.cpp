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

	swapCount.setFont(FONT_MGR.Get("fonts/Maplestory Light.ttf"));
	stageLevel.setFont(FONT_MGR.Get("fonts/Maplestory Light.ttf")); 

	backgroundPanel.setPosition({ startX,startY });
	swapCountPanel.setPosition({ startX + 30.f,startY + 30.f });
	targetCountPanel.setPosition({ startX + 150.f,startY + 30.f });
	stageLevelPanel.setPosition({ startX + 225.f,startY + 15.f });

	stageLevel.setCharacterSize(20.f);
	stageLevel.setFillColor(sf::Color::Black);
	Utils::SetOrigin(stageLevel, Origins::TC);
	stageLevel.setPosition(stageLevelPanel.getPosition() + sf::Vector2f(75.f, 5.f));

	swapCount.setCharacterSize(60.f);
	swapCount.setFillColor(sf::Color::Black);
	Utils::SetOrigin(swapCount, Origins::TC);
	swapCount.setPosition(swapCountPanel.getPosition() + sf::Vector2f(50.f, 10.f));
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
	window.draw(swapCount);
	window.draw(targetCountPanel);
	window.draw(stageLevelPanel);
	window.draw(stageLevel);
}

void StageUI::SetStageLevel(int level)
{
	stageLevel.setString("Stage " + std::to_string(level));
	Utils::SetOrigin(stageLevel, Origins::TC);
}

void StageUI::SetSwapCount(int count)
{
	if (count >= 10)
	{
		swapCount.setString(std::to_string(count));
	}
	else
	{
		swapCount.setString("0" + std::to_string(count));
	}
	Utils::SetOrigin(swapCount, Origins::TC);
}
