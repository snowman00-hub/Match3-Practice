#include "stdafx.h"
#include "SceneStage3.h"

SceneStage3::SceneStage3()
	: SceneGame(SceneIds::Stage3)
{
}

void SceneStage3::Init()
{
	stageLevel = 3;
	initialSwapCount = 13;
	swapCount = initialSwapCount;
	targetIsTile = true;
	targetIsWall = true;

	// -1 �� ����
	//  0 ����
	//  1 ��ֹ�
	static int initialBlockState[81] =
	{
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
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