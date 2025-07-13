#pragma once
#include "GameObject.h"

struct Target
{
	sf::Sprite* sprite;
	sf::Text countText;
	int* count;
};

class StageUI : public GameObject
{
protected:
	sf::Sprite backgroundPanel;
	sf::Sprite swapCountPanel;
	sf::Sprite targetCountPanel;
	sf::Sprite stageLevelPanel;

	sf::Text swapCount;
	sf::Text stageLevel;

	std::vector<Target> targets;

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

	void SetStageLevel(int level);
	void SetSwapCount(int count);
	void SetTarget(sf::Sprite* sprite, int* count);
	void UpdateTarget();
};