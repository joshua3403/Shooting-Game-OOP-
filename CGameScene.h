#pragma once

#include "stdafx.h"
#include "CBaseScene.h"
#include "CBaseObject.h"
#include "CList(STL).h"

class CGameScene : public CBaseScene
{

private:
	CList<CBaseObject*> ObjectList;
	int iStageIndex;
	int iEnemyCount;
	bool bPlayerWin;
	bool bEnemyWin;
	bool bEnter;
	LARGE_INTEGER fFreq;
	LARGE_INTEGER startShoot1;
	LARGE_INTEGER startShoot2;
	LARGE_INTEGER startShootBOSS;
	const char* Pause = "                                         PAUSE                                    \0";
	int iPlayerHp;
public:

	CGameScene(int stage);


	~CGameScene()
	{
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

	// ȭ���� ������ ��� �Ѿ��� �����ϴ� �Լ�
	void DeleteBullet();

	// �����̴� �Ѿ˰� ������Ʈ�� �浹�� ó���ϴ� �Լ�
	void BulletCollision();

	// ���� �ҷ��� �����ϴ� �Լ�
	void EnemyCreateBullet();

	// �÷��̾ ���������� ������ Ȯ���ϴ� �Լ�
	void CheckPlayerWin();

	// �÷��̾� �¸��� �÷��׸� ��ȯ
	bool GetPlayerWin();

	// ���� �¸� �÷��׸� ��ȯ
	bool GetEnemyWin();
	
	// �Ͻ� ���� ȭ�� ���
	void PrintPause();

	// �������̽� ������Ʈ ����
	void CreateInterface();

	// ���� ����
	void DeletePotion();

	// ���� �浹ó��
	void PotionCollision();

	// �������̽� ������Ʈ���� �÷��̾� ü���� ���Ž�Ŵ
	void UpdateInterface();
};