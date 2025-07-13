#pragma once
#include "GameObject.h"

class StageUI : public GameObject
{
protected:
	sf::Sprite backgroundPanel;
	sf::Sprite swapCountPanel;
	sf::Sprite targetCountPanel;
	sf::Sprite stageLevelPanel;

	sf::Text swapCount;
	sf::Text stageLevel;

	std::unordered_map<std::string, int> targets;

	const float startX = 50.f;
	const float startY = 10.f;

public:
	StageUI(const std::string& name = "");
	virtual ~StageUI() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetTarget(const std::string& texId, int count) { targets[texId] = count; }
	void SetStageLevel(int level);
	void SetSwapCount(int count);
};