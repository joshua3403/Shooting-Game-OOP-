#pragma once
#include "stdafx.h"
#include "CBaseScene.h"

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
	LARGE_INTEGER fFreq;
	LARGE_INTEGER start;

public:
	CEndingScene();

	void Update();

	void Sprite_Draw();

	bool GetEndingSceneEnd();

};
