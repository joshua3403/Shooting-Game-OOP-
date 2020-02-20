#pragma once
#include "stdafx.h"
#include "CBaseScene.h"

class CStageClearScene : public CBaseScene
{
private:
	char StageClear[dfSCREEN_HEIGHT][dfSCREEN_WIDTH] = {
"                                                                    __ __        \0",
"                    _____ _                  _____ _               |  |  |       \0",
"                   |   __| |_ ___ ___ ___   |     | |___ ___ ___   |  |  |       \0",
"                   |__   |  _| .'| . | -_|  |   --| | -_| .'| _ |  |__|__|       \0",
"                   |_____|_| |__,| _ |___|  |_____|_|___|__,|_|    |__|__|       \0",
"                             |___|									          \0",

};

	bool bStageClearSceneEnd;
	LARGE_INTEGER fFreq;
	LARGE_INTEGER start;

public:
	CStageClearScene();

	void Update();
	
	void Sprite_Draw();
	
	bool GetStageClearEnd();
};
