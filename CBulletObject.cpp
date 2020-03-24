#include "stdafx.h"
#include "CBulletObject.h"

CBulletObject::~CBulletObject()
{
}

bool CBulletObject::Action()
{
	switch (eWho)
	{
	case eWhoShoot::ENEMY:
		this->s_RelativePosition.iY++;
		break;
	case eWhoShoot::PLAYER:
		this->s_RelativePosition.iY--;
		break;
	}

	CheckCollision();
	return true;
}

void CBulletObject::Render()
{
	this->pGameScene->ScreenBuffer[this->s_RelativePosition.iY][this->s_RelativePosition.iX] = this->_cDisplay;
}

void CBulletObject::CheckCollision()
{
	if (s_RelativePosition.iY == 0 || s_RelativePosition.iY == dfSCREEN_HEIGHT - 2)
		pGameScene->GetBulletDelete(this);

	if (eWho == eWhoShoot::ENEMY)
	{
		std::list<CBaseObject*>::iterator itor = pGameScene->ObjectList.begin();

		for (; itor != pGameScene->ObjectList.end(); ++itor)
		{
			if ((*itor)->GetObjectType() == e_ObjectType::PLAYER)
			{
				if ((*itor)->GetObjectPosition().iX == s_RelativePosition.iX && (*itor)->GetObjectPosition().iY == s_RelativePosition.iY)
				{
					(*itor)->TakeDamage(_iDamage);
					pGameScene->GetBulletDelete(this);
				}
			}

		}
	}
	else if (eWho == eWhoShoot::PLAYER)
	{
		std::list<CBaseObject*>::iterator itor = pGameScene->ObjectList.begin();

		for (; itor != pGameScene->ObjectList.end(); ++itor)
		{
			if ((*itor)->GetObjectType() == e_ObjectType::ENEMY)
			{
				if ((*itor)->GetObjectPosition().iX == s_RelativePosition.iX && (*itor)->GetObjectPosition().iY == s_RelativePosition.iY)
				{
					(*itor)->TakeDamage(_iDamage);
					pGameScene->GetBulletDelete(this);
				}
			}

		}
	}
}

CBulletObject::eWhoShoot CBulletObject::GetWhoShoot()
{
	return this->eWho;
}

