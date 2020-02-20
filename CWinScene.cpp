#include "stdafx.h"
#include "CWinScene.h"

CWinScene::CWinScene() : bWinSceneEnd(false)
{
	cs_ClearScreen();

	QueryPerformanceFrequency(&fFreq);
	QueryPerformanceCounter(&start);
}

void CWinScene::Update()
{
	LARGE_INTEGER temp;
	QueryPerformanceCounter(&temp);

	__int64 now = (temp.QuadPart - start.QuadPart) / fFreq.QuadPart;

	Buffer_Clear();

	Sprite_Draw();

	if (now > 2)
		bWinSceneEnd = true;
}

void CWinScene::Sprite_Draw()
{
	for (int i = 8; i < 15; ++i)
	{
		cs_MoveCursor(0, i);
		printf(Win[i - 8]);
	}
}

bool CWinScene::GetWindSceneEnd()
{
	return this->bWinSceneEnd;
}
