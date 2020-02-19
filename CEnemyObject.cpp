#include "stdafx.h"
#include "CEnemyObject.h"
#include "CBulletObject.h"

bool CEnemyClass::Action()
{
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);
	
	__int64 moveTime = (now.QuadPart - startMove.QuadPart ) / fFreq.QuadPart;
	if (this->etype == EnemyType::NORMAL1)
	{
		if (moveTime >= 2)
		{			
			// 시작 시간 현재로 초기화
			QueryPerformanceCounter(&startMove);
			this->s_RelativePosition.iX += MAX_MOVE_RANGE1;
		}

	}
	else if (this->etype == EnemyType::BOSS)
	{
		if (moveTime >= 3)
		{
			// 시작 시간 현재로 초기화
			QueryPerformanceCounter(&startMove);
			this->s_RelativePosition.iX += MAX_MOVE_RANGE2;
		}
	}

	//if (shootTime >= this->ShootBulletTime)
	//{
	//	pGameScene->GetObjectList().push_back(new CBulletObject(pGameScene, CBulletObject::eWhoShoot::ENEMY, eObjectType::BULLET, this->s_RelativePosition.iX, this->s_RelativePosition.iY + 1, 1, this->GetDamage()));
	//	QueryPerformanceCounter(&startShoot);

	//}

	if (this->s_RelativePosition.iX < 0)
		this->s_RelativePosition.iX += dfSCREEN_WIDTH - 2;

	if (this->s_RelativePosition.iX > dfSCREEN_WIDTH - 2)
		this->s_RelativePosition.iX -= dfSCREEN_WIDTH - 2;

	return true;
}

void CEnemyClass::Render()
{
	if (this->bIsAlive)
	{
		pGameScene->ScreenBuffer[this->s_RelativePosition.iY][this->s_RelativePosition.iX] = cDisplay;
	}
}

CEnemyClass::~CEnemyClass()
{
}

int CEnemyClass::GetShootTime()
{
	return this->ShootBulletTime;
}

EnemyType CEnemyClass::GetEnemyType()
{
	return etype;
}

LARGE_INTEGER CEnemyClass::GetLARGEINTEGER()
{
	return startShoot;
}

void CEnemyClass::SetLARGEINTEGER(LARGE_INTEGER time)
{
	this->startShoot = time;
}
