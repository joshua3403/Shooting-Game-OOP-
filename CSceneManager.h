#pragma once
#include "stdafx.h"
#include "CBaseScene.h"
#include "CList(STL).h"


class CSceneManager
{
private:
	CBaseScene* pScene;
	int iStage;	
	static CSceneManager SceneManager;

private:

	CSceneManager() : iStage(0)
	{
	};

	~CSceneManager()
	{
	};
	
public:

	static CSceneManager* GetInstance()
	{
		return &SceneManager;
	}

	void ChangeScene(CBaseScene* Scene);

	void Run();

	CBaseScene* GetScenePointer();

	// GameScene ��ü���� �÷��̾��� �¸� �÷��׸� Ȯ���ϰ� true�� �Ǹ� stage�� ���� ����
	void PlayerWin();

	// stage���� ��ȯ
	int GetStage();
};