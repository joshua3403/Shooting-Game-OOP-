#include "stdafx.h"
#include "CPotionObject.h"

bool CPotionObject::Action()
{
	this->s_RelativePosition.iY++;

	CheckCollision();
	return false;
}

void CPotionObject::Render()
{
	this->pGameScene->ScreenBuffer[this->s_RelativePosition.iY][this->s_RelativePosition.iX] = this->_cDisplay;
}

void CPotionObject::CheckCollision()
{
	if (s_RelativePosition.iY == dfSCREEN_HEIGHT - 2)
		pGameScene->GetPotionDelete(this);

	std::list<CBaseObject*>::iterator itor = pGameScene->ObjectList.begin();
	for (; itor != pGameScene->ObjectList.end(); ++itor)
	{
		if ((*itor)->GetObjectType() == e_ObjectType::PLAYER)
		{
			if ((*itor)->GetObjectPosition().iX == s_RelativePosition.iX && (*itor)->GetObjectPosition().iY == s_RelativePosition.iY)
			{
				(*itor)->TakeHp(_iDamage);
				pGameScene->GetPotionDelete(this);
			}
		}
	}
}




