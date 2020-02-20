#pragma once
#include "stdafx.h"
#include "CBaseObject.h"

#include "CGameScene.h"

class CInterfaceObject : public CBaseObject
{
private:
	CGameScene* pGameScene;
	int Max_Hp = 0;
public:
	CInterfaceObject(CGameScene* GameScene, int hp, int damage) : CBaseObject(eObjectType::INTERFACEDISPLAY, 0, 0, 0, 0, 0)
	{
		Max_Hp = hp;
		iHp = hp;
		iDamage = damage;
	};

	bool Action();

	void Render();

	void UpdateHp(int hp);

	void InterfaceClear();
};