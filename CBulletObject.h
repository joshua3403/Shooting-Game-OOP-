#pragma once
#include "stdafx.h"
#include "CBaseObject.h"
#include "CGameScene.h"

class CBulletObject : public CBaseObject
{
public:
	enum eWhoShoot
	{
		PLAYER = 0,
		ENEMY
	};

private:
	eWhoShoot eWho;
	CGameScene* pGameScene;

public:
	CBulletObject(CGameScene* GameScene,eWhoShoot who, e_ObjectType _ObjectType, int X, int Y, int Hp, int Damage) : CBaseObject(_ObjectType, X, Y, Hp, Damage, '0')
	{
		eWho = who;
		pGameScene = GameScene;
		switch (who)
		{
		case eWhoShoot::PLAYER:
			this->_cDisplay = '^';
			break;
		case eWhoShoot::ENEMY:
			this->_cDisplay = '#';
			break;
		}
	}

	~CBulletObject();

	bool Action();

	void Render();

	void CheckCollision();

	eWhoShoot GetWhoShoot();
};