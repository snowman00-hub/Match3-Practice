#include "stdafx.h"
#include "SceneStage2.h"

SceneStage2::SceneStage2()
	: SceneGame(SceneIds::Stage2)
{
}

void SceneStage2::Init()
{
	stageLevel = 2;
	initialSwapCount = 9;
	swapCount = initialSwapCount;
	targetIsTile = false;
	targetIsWall = true;

	// -1 �� ����
	//  0 ����
	//  1 ��ֹ�
	static int initialBlockState[81] =
	{
		0,0,0,0,0,0,0,0,0,
		1,1,0,0,0,0,0,1,1,
		1,0,1,0,0,0,1,0,1,
		1,0,0,1,0,1,0,0,1,
		1,0,0,0,1,0,0,0,1,
		1,0,0,1,0,1,0,0,1,
		1,0,1,0,0,0,1,0,1,
		1,1,0,0,0,0,0,1,1,
		1,1,1,1,1,1,1,1,1,
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
		0,0,0,0,0,0,0,0,0
	};

	//

	SceneGame::Init();

	board->SetInitialBlockState(initialBlockState);
	board->SetInitialTileState(initialTileState);
}