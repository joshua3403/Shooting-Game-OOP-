#pragma once
#include "stdafx.h"
#include "CBaseScene.h"
#include "CSceneManager.h"

class CEndingScene : public CBaseScene
{
private:
	char Lose[dfSCREEN_HEIGHT][dfSCREEN_WIDTH] = {
"                                              _			                       \0",
"                               _ _ ___ _ _   | |___ ___ ___                       \0",
"                              | | | . | | |  | | . | _-| -_|                      \0",
"                              |_  |___|___|  |_|___|___|___|                      \0",
"                              |___|						                       \0",
"                                                                                  \0",
"                                       Try Again :-(                              \0"
	};
	bool bEndingSceneEnd;
	DWORD _Start;
	DWORD _End;
	CSceneManager* pSceneManager;

public:
	CEndingScene(CSceneManager* SceneManager);

	void Update();

	void Sprite_Draw();
};
