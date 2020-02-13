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
	LARGE_INTEGER start;

public:
	CEnemyClass(CGameScene* GameScene, eObjectType ObjectType, int X, int Y, int Hp, int Damage, char Display, EnemyType type) :CBaseObject(ObjectType, X, Y, Hp, Damage, Display), etype(type), pGameScene(GameScene), bMoveFlag(false)
	{
		QueryPerformanceFrequency(&fFreq);
		QueryPerformanceCounter(&start);
	}

	bool Action();

	void Render();
};