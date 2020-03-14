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
	enum eState
	{
		CREATETITLE = 0,
		TITLE,
		CREATELOADING,
		LOADING,
		CREATEPLAY,
		PLAYING,
		CREATEDIE,
		DIE,
		CREATESTAGECLEAR,
		STAGECLEAR,
		CREATEWIN,
		WIN,
	};

	eState State;

private:

	CSceneManager() : iStage(1), State(eState::TITLE)
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