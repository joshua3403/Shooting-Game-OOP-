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

	if (_iHp > MAX_HP)
		_iHp = MAX_HP;

	CheckDelete();
	return true;
}

void CPlayerObject::Render()
{
	if(this->_bIsAlive)
		pGameScene->ScreenBuffer[this->s_RelativePosition.iY][this->s_RelativePosition.iX] = this->_cDisplay;
	else
	{
		pGameScene->ScreenBuffer[this->s_RelativePosition.iY][this->s_RelativePosition.iX] = ' ';
	}
}

void CPlayerObject::CheckDelete()
{
	if (_iHp == 0) 
	{
		pGameScene->GetPlayerLose();
	}
}




CPlayerObject::~CPlayerObject()
{
}
