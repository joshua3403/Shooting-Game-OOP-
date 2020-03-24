#include "stdafx.h"
#include "CWinScene.h"

CWinScene::CWinScene(CSceneManager* SceneManager) : bWinSceneEnd(false)
{
	cs_ClearScreen();
	_pSceneManager = SceneManager;

	_startTime = GetTickCount64();

}

void CWinScene::Update()
{
	LARGE_INTEGER temp;
	QueryPerformanceCounter(&temp);

	int now = (int)(GetTickCount64() - _startTime) / 1000;

	Buffer_Clear();

	Sprite_Draw();

	if (now > 2)
	{
		_pSceneManager->ChangeScene(eState::CREATETITLE);
	}
}

void CWinScene::Sprite_Draw()
{
	for (int i = 8; i < 15; ++i)
	{
		cs_MoveCursor(0, i);
		printf(Win[i - 8]);
	}
}


