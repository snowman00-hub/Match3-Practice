#include "stdafx.h"
#include "SceneStage1.h"

SceneStage1::SceneStage1()
	: SceneGame(SceneIds::Stage1)
{
}

void SceneStage1::Init()
{
	stageLevel = 1;
	initialSwapCount = 18;
	swapCount = initialSwapCount;
	targetIsTile = true;
	targetIsWall = true;

	// -1 �� ����
	//  0 ����
	//  1 ��ֹ�
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

	// -1 �� ����
	//  0 ����Ʈ
	//  1 ����Ʈ��
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

	SceneGame::Init();

	board->SetInitialBlockState(initialBlockState);
	board->SetInitialTileState(initialTileState);
}