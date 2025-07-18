#include "stdafx.h"
#include "SceneDev1.h"

SceneDev1::SceneDev1()
	: SceneGame(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	stageLevel = 999;
	initialSwapCount = 99;
	swapCount = initialSwapCount;
	targetIsTile = true;
	targetIsWall = true;

	// -1 �� ����
	//  0 ����
	//  1 ��ֹ�
	static int initialBlockState[81] =
	{
		-1,-1,-1,0,0,0,-1,-1,-1,
		-1,-1,-1,0,0,0,-1,-1,-1,
		-1,-1,-1,0,0,0,-1,-1,-1,
		1,-1,-1,-1,-1,-1,-1,-1,1,
		0,-1,-1,-1,-1,-1,-1,-1,0,
		0,-1,-1,-1,-1,-1,-1,-1,0,
		0,-1,-1,-1,-1,-1,-1,-1,0,
		1,-1,-1,-1,-1,-1,-1,-1,1,
		1,1,1,0,0,0,1,1,1,
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
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1,1
	};

	SceneGame::Init();

	board->SetInitialBlockState(initialBlockState);
	board->SetInitialTileState(initialTileState);
}