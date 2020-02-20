#include "stdafx.h"
#include "CEndingScene.h"

CEndingScene::CEndingScene() : bEndingSceneEnd(false)
{
	cs_ClearScreen();

	QueryPerformanceFrequency(&fFreq);
	QueryPerformanceCounter(&start);
}

void CEndingScene::Update()
{
	LARGE_INTEGER temp;
	QueryPerformanceCounter(&temp);

	__int64 now = (temp.QuadPart - start.QuadPart) / fFreq.QuadPart;

	Buffer_Clear();

	Sprite_Draw();

	if (now > 2)
		bEndingSceneEnd = true;
}

void CEndingScene::Sprite_Draw()
{
	for (int i = 8; i < 15; ++i)
	{
		cs_MoveCursor(0, i);
		printf(Lose[i - 8]);
	}
}

bool CEndingScene::GetEndingSceneEnd()
{
	return this->bEndingSceneEnd;
}
