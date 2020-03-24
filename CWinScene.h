#pragma once
#include "stdafx.h"
#include "CBaseScene.h"
#include "CSceneManager.h"

class CWinScene : public CBaseScene
{
private:
	char Win[dfSCREEN_HEIGHT][dfSCREEN_WIDTH] = {
"                                                      _                            \0",
"                                 _ _ ___ _ _    _ _ _|_|___                        \0",
"                                | | | . | | |  | | | | |   |                       \0",
"                                |_  |___|___|  |_____|_|_|_|                       \0",
"                                |___|                                              \0",
"                                                                                   \0",
"                                     Thanks to Play :-)                            \0",
	};

	bool bWinSceneEnd;
	DWORD _startTime;
	CSceneManager* _pSceneManager;

public:
	CWinScene(CSceneManager* SceneManager);

	void Update();

	void Sprite_Draw();

};