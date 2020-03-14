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

	EnemyType GetEnemyType();

	LARGE_INTEGER GetLARGEINTEGER();

	void SetLARGEINTEGER(LARGE_INTEGER time);
};