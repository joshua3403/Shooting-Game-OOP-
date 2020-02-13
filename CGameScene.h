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
		// ���Ӿ� ��ü�� ���� �� �� �÷��̾� ������Ʈ ����.
		ObjectList.push_back(new CPlayerObject(this));
		// ��ü�� ���� �� �� ó�� 1 ���������� ���õ� ������ ����
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