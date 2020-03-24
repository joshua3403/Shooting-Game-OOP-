#include "stdafx.h"
#include "CEndingScene.h"

CEndingScene::CEndingScene(CSceneManager* SceneManager) : bEndingSceneEnd(false)
{
	pSceneManager = SceneManager;
	cs_ClearScreen();

	_Start = GetTickCount64();
}

void CEndingScene::Update()
{
	_End = GetTickCount64();

	__int64 now = (_End - _Start) / 1000;

	Buffer_Clear();

	Sprite_Draw();

	if (now > 2)
	{
		bEndingSceneEnd = true;
		pSceneManager->ChangeScene(eState::CREATETITLE);
	}
}

void CEndingScene::Sprite_Draw()
{
	for (int i = 8; i < 15; ++i)
	{
		cs_MoveCursor(0, i);
		printf(Lose[i - 8]);
	}
}
