#pragma once
#include "stdafx.h"
#include "CBaseObject.h"
#include "CGameScene.h"

class CPotionObject : public CBaseObject
{
private:
	CGameScene* pGameScene;

public:
	CPotionObject(CGameScene* GameScene, int X, int Y) : CBaseObject(e_ObjectType::POTION, X, Y, 0, 1, '0')
	{
		pGameScene = GameScene;

	};

	bool Action();

	void Render();

	void CheckCollision();
};