#include "stdafx.h"
#include "CTitleScene.h"

CTitleScene::CTitleScene() : intro_print(false), bEnterEntered(false)
{
	QueryPerformanceFrequency(&fFreq);
	QueryPerformanceCounter(&start);
}

CTitleScene::~CTitleScene()
{
}

void CTitleScene::Update()
{
	Buffer_Clear();

	if (!intro_print)
		PrintIntro();
	else
	{
		Sprite_Draw();
		bEnterEntered = GetKeyInput();
	}

}

void CTitleScene::PrintIntro()
{
	LARGE_INTEGER temp;
	QueryPerformanceCounter(&temp);
	__int64 time = ((temp.QuadPart - start.QuadPart) / fFreq.QuadPart) * 1.5;

	for (int i = 0; i < time; ++i)
	{
		cs_MoveCursor(0, i);
		printf(szTitleBuffer[i]);
	}
	
	if (time >= dfSCREEN_HEIGHT - 13)
	{
		time = dfSCREEN_HEIGHT;
		intro_print = true;
	}
}

void CTitleScene::Sprite_Draw()
{
	for (int i = 0; i < dfSCREEN_HEIGHT; ++i)
	{
		cs_MoveCursor(0, i);
		printf(szTitleBuffer[i]);
	}
}

bool CTitleScene::GetKeyInput()
{
	bool bEnter = false;

	bEnter = GetAsyncKeyState(VK_RETURN) & 0x8000;

	return bEnter;
}

bool CTitleScene::GetEnterEntered()
{
	return this->bEnterEntered;
}
