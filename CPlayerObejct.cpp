#include "stdafx.h"
#include "CPlayerObejct.h"

bool CPlayerObject::Action()
{
	for (const auto input : l_Player_Input)
	{
		switch (input)
		{
		case KeyInput::DOWN:
			this->s_RelativePosition.iY++;
			break;
		case KeyInput::UP:
			this->s_RelativePosition.iY--;
			break;
		case KeyInput::LEFT:
			this->s_RelativePosition.iX--;
			break;
		case KeyInput::RIGHT:
			this->s_RelativePosition.iX++;
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


	}
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
