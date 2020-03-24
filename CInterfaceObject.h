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
	CInterfaceObject(CGameScene* GameScene, int hp, int damage) : CBaseObject(e_ObjectType::INTERFACEDISPLAY, 0, 0, 0, 0, 0)
	{
		Max_Hp = hp;
		_iHp = hp;
		_iDamage = damage;
	};

	~CInterfaceObject();

	bool Action();

	void Render();

	void UpdateHp(int hp);

	void InterfaceClear();
};