#include "stdafx.h"
#include "CStageClearScene.h"

CStageClearScene::CStageClearScene() : bStageClearSceneEnd(false)
{
	cs_ClearScreen();

	QueryPerformanceFrequency(&fFreq);
	QueryPerformanceCounter(&start);
}

void CStageClearScene::Update()
{
	LARGE_INTEGER temp;
	QueryPerformanceCounter(&temp);

	__int64 now = (temp.QuadPart - start.QuadPart) / fFreq.QuadPart;

	Buffer_Clear();

	Sprite_Draw();

	if (now > 2)
		bStageClearSceneEnd = true;
}

void CStageClearScene::Sprite_Draw()
{
	for (int i = 8; i < 14; ++i)
	{
		cs_MoveCursor(0, i);
		printf(StageClear[i - 8]);
	}
}

bool CStageClearScene::GetStageClearEnd()
{
	return this->bStageClearSceneEnd;
}
