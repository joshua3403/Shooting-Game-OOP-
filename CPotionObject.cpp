#include "stdafx.h"
#include "CPotionObject.h"

bool CPotionObject::Action()
{
	this->s_RelativePosition.iY++;

	return false;
}

void CPotionObject::Render()
{
	this->pGameScene->ScreenBuffer[this->s_RelativePosition.iY][this->s_RelativePosition.iX] = this->_cDisplay;
}


