#pragma once

#include "stdafx.h"
#include "CBaseObject.h"
#include "CGameScene.h"

#define MAX_MOVE_RANGE1 2
#define MAX_MOVE_RANGE2 4

enum EnemyType
{
	NORMAL1 = 0,
	NORMAL2,
	BOSS,
};

class CEnemyClass : public CBaseObject
{
private:
	EnemyType etype;
	CGameScene* pGameScene;
	LARGE_INTEGER fFreq;
	LARGE_INTEGER startMove;
	LARGE_INTEGER startShoot;
	int ShootBulletTime;

public:
	CEnemyClass(CGameScene* GameScene, eObjectType ObjectType, int X, int Y, int Hp, int Damage, char Display, EnemyType type, int time) :CBaseObject(ObjectType, X, Y, Hp, Damage, Display), etype(type), pGameScene(GameScene)
	{
		QueryPerformanceFrequency(&fFreq);
		QueryPerformanceCounter(&startMove);
		QueryPerformanceCounter(&startShoot);

		ShootBulletTime = time;
	}

	bool Action();

	void Render();

	~CEnemyClass();

	int GetShootTime();

	// 적 객체에서 시간마다 총알을 생성하는 함수 <- 이 함수가 CEnemyClass에 들어가는게 맞다고 생각하지만 이럴 수 밖에 없었음
	EnemyType GetEnemyType();

	LARGE_INTEGER GetLARGEINTEGER();

	void SetLARGEINTEGER(LARGE_INTEGER time);
};