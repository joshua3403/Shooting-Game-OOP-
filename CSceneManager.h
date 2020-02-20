#pragma once
#include "stdafx.h"
#include "CBaseScene.h"
#include "CList(STL).h"

#define MAX_STAGE 2

class CSceneManager
{
private:
	CBaseScene* pScene;
	int iStage;	
	static CSceneManager SceneManager;

private:

	CSceneManager() : iStage(1)
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
	void StageClear();

	// stage���� ��ȯ
	int GetStage();

	void Reset();
};