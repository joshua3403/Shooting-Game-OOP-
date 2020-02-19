#include "stdafx.h"
#include "CLoadingScene.h"

CLoadingScene::CLoadingScene() : bLoadingSceneEnd(false)
{
	QueryPerformanceFrequency(&fFreq);
	QueryPerformanceCounter(&start);
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
		bLoadingSceneEnd = true;
	}
}

void CLoadingScene::PrintOne()
{
	for (int i = 0; i < dfSCREEN_HEIGHT; ++i)
	{
		cs_MoveCursor(0, i);
		printf(One[i]);
	}
}

void CLoadingScene::PrintTwo()
{
	for (int i = 0; i < dfSCREEN_HEIGHT; ++i)
	{
		cs_MoveCursor(0, i);
		printf(Two[i]);
	}
}

void CLoadingScene::PrintThree()
{
	for (int i = 0; i < dfSCREEN_HEIGHT; ++i)
	{
		cs_MoveCursor(0, i);
		printf(Three[i]);
	}
}

bool CLoadingScene::GetLoadingSceneEnd()
{
	return this->bLoadingSceneEnd;
}

void CLoadingScene::Sprite_Draw()
{
}
