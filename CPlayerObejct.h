#pragma once

#include "CBaseObject.h"
#include "CList(STL).h"
#include "CGameScene.h"

// 키보드 입력을 구분할 열거체
enum class KeyInput
{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3,
	ATTACK = 4,
	COUNT = 5
};


class CPlayerObject : public CBaseObject
{
private:
	CGameScene* pGameScene;
public:
	CPlayerObject(CGameScene* GameScene) : CBaseObject(eObjectType::PLAYER, 40, 22,5, 1, 'A')
	{
		this->pGameScene = GameScene;
	}

	bool Action();

	void Render();


public:
	static CList<KeyInput> l_Player_Input;

};