#include "stdafx.h"
#include "CEnemyObject.h"
#include "CBulletObject.h"
#include "CPotionObject.h"


bool CEnemyClass::Action()
{
	int moveTime = (int)(GetTickCount64() - _startTime) / 1000;
	int shootTimte = (int)(GetTickCount64() - _startShootTime) / 1000;

	if (_etype == EnemyType::NORMAL1)
	{
		if (moveTime >= 2)
		{			

			s_RelativePosition.iX += MAX_MOVE_RANGE1;
			_startTime = GetTickCount64();

		}

	}
	else if (_etype == EnemyType::BOSS)
	{
		if (moveTime >= 3)
		{

			s_RelativePosition.iX += MAX_MOVE_RANGE2;
			_startTime = GetTickCount64();
		}
	}

	if (shootTimte >= _ShootBulletTime)
	{
		_pGameScene->ObjectList.push_back(new CBulletObject(_pGameScene, CBulletObject::eWhoShoot::ENEMY, e_ObjectType::BULLET, s_RelativePosition.iX, s_RelativePosition.iX + 1, 1, _iDamage));
		_startShootTime = GetTickCount64();
	}

	// 시작 시간 현재로 초기화


	if (s_RelativePosition.iX < 0)
		s_RelativePosition.iX += dfSCREEN_WIDTH - 2;

	if (s_RelativePosition.iX > dfSCREEN_WIDTH - 2)
		s_RelativePosition.iX -= dfSCREEN_WIDTH - 2;

	CheckDie();

	return true;
}

void CEnemyClass::Render()
{
	if (this->_bIsAlive)
	{
		_pGameScene->ScreenBuffer[this->s_RelativePosition.iY][this->s_RelativePosition.iX] = _cDisplay;
	}
}

CEnemyClass::~CEnemyClass()
{
}

int CEnemyClass::GetShootTime()
{
	return this->_ShootBulletTime;
}

//-------------------------------------------
// 역활 : 죽었는지 체크, 죽으면 일정 확률로 포션 생성, 죽었으면 GameScene의 ObjectList에서 삭제 요청
// 인자 : void
// 반환 : void
void CEnemyClass::CheckDie()
{
	if (_iHp == 0)
	{
		int percent = rand() % 100;
		if (percent < 20)
		{
			_pGameScene->ObjectList.push_back(new CPotionObject(_pGameScene, s_RelativePosition.iX, s_RelativePosition.iY));
		}

		_pGameScene->GetEnemyDelete(this);
		delete this;
	}
}

EnemyType CEnemyClass::GetEnemyType()
{
	return _etype;
}


