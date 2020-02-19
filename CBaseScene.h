#pragma once

#include "stdafx.h"

class CBaseScene
{
public:

	char ScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

	virtual ~CBaseScene();

	virtual void Update() = 0;

	virtual void Sprite_Draw() = 0;
	
	void Buffer_Clear(void);	
};