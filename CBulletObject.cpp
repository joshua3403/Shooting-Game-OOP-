#include "stdafx.h"
#include "CBulletObject.h"

CBulletObject::~CBulletObject()
{
}

bool CBulletObject::Action()
{
	switch (this->eWho)
	{
	case eWhoShoot::ENEMY:
		this->s_RelativePosition.iY++;
		break;
	case eWhoShoot::PLAYER:
		this->s_RelativePosition.iY--;
		break;
	}

	// 불렛의 소멸은 GameScene에서 관리 하는 걸로
	return true;
}

void CBulletObject::Render()
{
	this->pGameScene->ScreenBuffer[this->s_RelativePosition.iY][this->s_RelativePosition.iX] = this->cDisplay;
}

CBulletObject::eWhoShoot CBulletObject::GetWhoShoot()
{
	return this->eWho;
}

