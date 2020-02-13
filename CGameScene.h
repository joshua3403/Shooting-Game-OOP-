#pragma once

#include "stdafx.h"
#include "CBaseScene.h"

class CGameScene : public CBaseScene
{

private:
	CList<CBaseObject*> ObjectList;
	int iStageIndex;
public:

	CGameScene() : iStageIndex(0)
	{
		// 게임씬 객체가 생성 될 때 플레이어 오브젝트 생성.
		ObjectList.push_back(new CPlayerObject(this));
		// 객체가 생성 될 때 처음 1 스테이지에 관련된 적들을 생성
		CreateEnemy(iStageIndex);
	}

	~CGameScene()
	{
	}
	void Update();

	void Sprite_Draw();

	void GetKeyInput();

	void CreateEnemy(int iStageIndex);

};