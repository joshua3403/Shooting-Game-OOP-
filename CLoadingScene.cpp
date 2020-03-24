#include "stdafx.h"
#include "CLoadingScene.h"

CLoadingScene::CLoadingScene(int stage, CSceneManager* SceneManager) : _Stage(stage), _pSceneManager(SceneManager)
{
	cs_ClearScreen();
	QueryPerformanceFrequency(&fFreq);
	QueryPerformanceCounter(&start);
	PrintStageInfo();
	_Stage = 0;
}

CLoadingScene::~CLoadingScene()
{
}

void CLoadingScene::Update()
{
	Buffer_Clear();
	LARGE_INTEGER temp;
	QueryPerformanceCounter(&temp);
	__int64 time = (temp.QuadPart - this->start.QuadPart) / this->fFreq.QuadPart;

	if (time <= 1)
		PrintThree();
	else if (time > 1 && time <= 2)
		PrintTwo();
	else if (time > 2 && time <= 3)
		PrintOne();
	else
	{
		_pSceneManager->ChangeScene(eState::CREATEPLAY);
	}
}

void CLoadingScene::PrintOne()
{
	for (int i = 0; i < dfSCREEN_HEIGHT; ++i)
	{
		cs_MoveCursor(0, i);
		if (i == 18)
		{
			printf(StageInfo);
		}
		else
		{
			printf(One[i]);

		}
	}
}

void CLoadingScene::PrintTwo()
{
	for (int i = 0; i < dfSCREEN_HEIGHT; ++i)
	{
		cs_MoveCursor(0, i);
		if (i == 18)
		{
			printf(StageInfo);
		}
		else
		{
			printf(Two[i]);

		}
	}
}

void CLoadingScene::PrintThree()
{
	for (int i = 0; i < dfSCREEN_HEIGHT; ++i)
	{
		cs_MoveCursor(0, i);
		if (i == 18)
		{
			printf(StageInfo);
		}
		else
		{
			printf(Three[i]);
		}
	}
}

void CLoadingScene::Sprite_Draw()
{
}

void CLoadingScene::PrintStageInfo()
{
	sprintf(StageInfo, "                                      STAGE : %d                                  \0", this->_Stage);
}

