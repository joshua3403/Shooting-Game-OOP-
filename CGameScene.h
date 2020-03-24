#pragma once

#include "stdafx.h"
#include "CBaseScene.h"
#include "CBaseObject.h"
#include "CSceneManager.h"

class CGameScene : public CBaseScene
{

private:
	CSceneManager* pSceneManager;
	int _iStageIndex;
	int _iEnemyCount;
	bool _bPlayerWin;
	bool _bEnemyWin;
	bool _bEnter;
	LARGE_INTEGER fFreq;
	const char* Pause = "                                         PAUSE                                    \0";
	int _iPlayerHp;
public:

	CGameScene(CSceneManager* SceneManager,int stage);


	~CGameScene()
	{
		std::list<CBaseObject*>::iterator it = ObjectList.begin();
		while (it != ObjectList.end())
		{
			if((*it)!= nullptr)
				delete (*it);
			it++;
		}
		ObjectList.clear();
	}

	// ���� ���� ������ ����Ǵ� �Լ�
	void Update();

	// ������Ʈ ����Ʈ�� ��ȸ�ϸ鼭 ������Ʈ�� Action�� Render�Լ��� �����Ŵ
	void ObjectPlay();

	// ȭ�鿡 ����Ʈ �ϴ� �Լ�
	void Sprite_Draw();

	// Ű���� �Է��� �޾� ����Ʈ�� �����ϴ� �Լ�
	void GetKeyInput();

	// ���������� ������ �޾� �ش� ������ �����ϴ� �Լ�
	void CreateEnemy(int iStageIndex);

	// �� ������Ʈ�κ��� �Ҹ��� ���޹޴� �Լ�
	void GetEnemyDelete(void* enemy);

	// �Ѿ��� �Ҹ��� ���޹޴� �Լ�
	void GetBulletDelete(void* bullet);

	// ������ �Ҹ��� ���޹޴� �Լ�
	void GetPotionDelete(void* potion);

	// �÷��̾� ������Ʈ�κ��� �÷��̾��� ����� ���޸���
	void GetPlayerLose();

	// �� �Ŵ������� �÷��̾� �й� �������� ��ȯ�� ����
	void ChangeScenePlayerLose();

	// �� �Ŵ������� �÷��̾� �������� Ŭ��� ����
	void CheckStageClear();

	// �Ͻ� ���� ȭ�� ���
	void PrintPause();

	// �������̽� ������Ʈ ����
	void CreateInterface();

	// �������̽� ������Ʈ���� �÷��̾� ü���� ���Ž�Ŵ
	void UpdateInterface();


public:
	std::list<CBaseObject*> ObjectList;

};