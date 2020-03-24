#pragma once

#include "stdafx.h"
#include "CBaseObject.h"
#include "CGameScene.h"

#define MAX_MOVE_RANGE1 2
#define MAX_MOVE_RANGE2 4

enum class EnemyType
{
	NORMAL1 = 0,
	NORMAL2,
	BOSS,
};

class CEnemyClass : public CBaseObject
{
private:
	EnemyType _etype;
	CGameScene* _pGameScene;
	DWORD _startTime;
	DWORD _startShootTime;
	int _ShootBulletTime;

public:
	CEnemyClass(CGameScene* GameScene, e_ObjectType _ObjectType, int X, int Y, int Hp, int Damage, char Display, EnemyType type, int time) :CBaseObject(_ObjectType, X, Y, Hp, Damage, Display), _etype(type), _pGameScene(GameScene)
	{
		_startTime = GetTickCount64();
		_startShootTime = GetTickCount64();
		_ShootBulletTime = time;
	}

	bool Action();

	void Render();

	~CEnemyClass();

	int GetShootTime();

	// 죽었는지 체크
	void CheckDie();

	EnemyType GetEnemyType();



};