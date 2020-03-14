#include "stdafx.h"
#include "CPlayerObejct.h"
#include "CBulletObject.h"

bool CPlayerObject::Action()
{
	CList<int>::iterator itor = l_Player_Input.begin();
	while(true)
	{
		if (itor == l_Player_Input.end())
		{
			break;
		}
		int input = (*itor);
		switch (input)
		{
		case static_cast<int>(KeyInput::DOWN):
			this->s_RelativePosition.iY++;
			break;
		case static_cast<int>(KeyInput::UP):
			this->s_RelativePosition.iY--;
			break;
		case static_cast<int>(KeyInput::LEFT):
			this->s_RelativePosition.iX--;
			break;
		case static_cast<int>(KeyInput::RIGHT):
			this->s_RelativePosition.iX++;
			break;
		default :
			break;
		}

		// 플레이어의 이동 범위를 제한
		if (this->s_RelativePosition.iX <= 0)
			this->s_RelativePosition.iX = 0;

		if (this->s_RelativePosition.iX >= dfSCREEN_WIDTH - 2)
			this->s_RelativePosition.iX = dfSCREEN_WIDTH - 2;

		if (this->s_RelativePosition.iY >= dfSCREEN_HEIGHT - 2)
			this->s_RelativePosition.iY = dfSCREEN_HEIGHT - 2;

		if (this->s_RelativePosition.iY <= dfSCREEN_HEIGHT - 5)
			this->s_RelativePosition.iY = dfSCREEN_HEIGHT - 5;

		itor = l_Player_Input.erase(itor);
	}


	if (this->iHp > MAX_HP)
		iHp = MAX_HP;
	return true;
}

void CPlayerObject::Render()
{
	if(this->bIsAlive)
		pGameScene->ScreenBuffer[this->s_RelativePosition.iY][this->s_RelativePosition.iX] = this->cDisplay;
	else
	{
		pGameScene->ScreenBuffer[this->s_RelativePosition.iY][this->s_RelativePosition.iX] = ' ';
	}
}

CPlayerObject::~CPlayerObject()
{
}
