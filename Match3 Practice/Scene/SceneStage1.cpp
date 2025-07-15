#include "stdafx.h"
#include "SceneStage1.h"

SceneStage1::SceneStage1()
	: SceneGame(SceneIds::Stage1)
{
}

void SceneStage1::Init()
{
	stageLevel = 1;
	initialSwapCount = 16;
	swapCount = initialSwapCount;
	targetIsTile = true;
	targetIsWall = true;

	// -1 빈 공간
	//  0 보석
	//  1 장애물
	static int initialBlockState[81] =
	{
		-1,0,0,0,0,0,0,0,-1,
		0,-1,0,0,0,0,0,-1,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,-1,0,0,0,0,
		0,0,0,-1,1,-1,0,0,0,
		0,0,0,0,-1,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,-1,0,0,0,0,0,-1,0,
		-1,0,0,0,0,0,0,0,-1
	};

	// -1 빈 공간
	//  0 디폴트
	//  1 페인트된
	static int initialTileState[81] =
	{
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,1,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0
	};

	//

	background.setTexture(TEXTURE_MGR.Get("graphics/bg_sky.png"));

	ui = (StageUI*)AddGameObject(new StageUI("UI"));
	ui->SetStageLevel(stageLevel);
	ui->SetSwapCount(&swapCount);
	ui->UpdateSwapCount();
	redTile.setTexture(TEXTURE_MGR.Get("graphics/tiles.png"));
	redTile.setTextureRect(sf::IntRect(Tile::SIZE, 0, Tile::SIZE, Tile::SIZE));
	wall.setTexture(TEXTURE_MGR.Get("graphics/blocks.png"));
	wall.setTextureRect(sf::IntRect(0, 0, Block::SIZE, Block::SIZE));

	relocateMessage.setFont(FONT_MGR.Get("fonts/Maplestory Light.ttf"));
	relocateMessage.setCharacterSize(80);
	relocateMessage.setFillColor(sf::Color::Yellow);
	relocateMessage.setString(L"재배치!");
	Utils::SetOrigin(relocateMessage, Origins::MC);
	relocateMessage.setPosition({ 600.f,150.f });

	clearMessage.setFont(FONT_MGR.Get("fonts/Maplestory Light.ttf"));
	clearMessage.setCharacterSize(80);
	clearMessage.setFillColor(sf::Color::Yellow);
	clearMessage.setString("Clear!");
	Utils::SetOrigin(clearMessage, Origins::MC);
	clearMessage.setPosition({ 360.f,380.f });

	defeatMessage.setFont(FONT_MGR.Get("fonts/Maplestory Light.ttf"));
	defeatMessage.setCharacterSize(80);
	defeatMessage.setFillColor(sf::Color::Blue);
	defeatMessage.setString("Defeat");
	Utils::SetOrigin(defeatMessage, Origins::MC);
	defeatMessage.setPosition({ 360.f,380.f });

	board = (Board*)AddGameObject(new Board());
	board->SetInitialBlockState(initialBlockState);
	board->SetInitialTileState(initialTileState);

	Scene::Init();

	if (targetIsTile)
	{
		remainTileCount++;
		ui->SetTarget(&redTile, &remainTileCount);
		remainTileCount--;
	}

	if (targetIsWall)
	{
		remainWallCount++;
		ui->SetTarget(&wall, &remainWallCount);
		remainWallCount--;
	}
}