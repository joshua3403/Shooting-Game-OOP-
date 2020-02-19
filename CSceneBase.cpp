#include "stdafx.h"
#include "CBaseScene.h"

CBaseScene::~CBaseScene()
{
}

void CBaseScene::Buffer_Clear(void)
{
	for (int i = 0; i < dfSCREEN_HEIGHT; ++i)
	{
		for (int j = 0; j < dfSCREEN_WIDTH - 1; ++j)
		{
			ScreenBuffer[i][j] = ' ';
		}
		ScreenBuffer[i][dfSCREEN_WIDTH - 1] = '\0';
	}
}
