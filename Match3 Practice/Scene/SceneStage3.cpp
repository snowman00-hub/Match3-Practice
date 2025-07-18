#include "stdafx.h"
#include "SceneStage3.h"

SceneStage3::SceneStage3()
	: SceneGame(SceneIds::Stage3)
{
}

void SceneStage3::Init()
{
	stageLevel = 3;
	initialSwapCount = 20;
	swapCount = initialSwapCount;
	targetIsTile = true;
	targetIsWall = false;

	// -1 빈 공간
	//  0 보석
	//  1 장애물
	static int initialBlockState[81] =
	{
		-1,-1,0,0,0,0,0,-1,-1,
		-1,0,0,0,0,0,0,0,-1,
		0,0,0,0,0,0,0,0,0,
		0,0,0,-1,-1,-1,0,0,0,
		0,0,0,-1,-1,-1,0,0,0,
		0,0,0,-1,-1,-1,0,0,0,
		0,0,0,0,-1,0,0,0,0,
		-1,0,0,0,0,0,0,0,-1,
		-1,-1,0,0,0,0,0,-1,-1,
	};

	// -1 빈 공간
	//  0 디폴트
	//  1 페인트된
	static int initialTileState[81] =
	{
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,1,1,1,0,0,0,
		0,0,1,0,0,0,1,0,0,
		0,0,1,0,0,0,1,0,0,
		0,0,1,0,0,0,1,0,0,
		0,0,0,1,0,1,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0
	};

	//

	SceneGame::Init();

	board->SetInitialBlockState(initialBlockState);
	board->SetInitialTileState(initialTileState);
}