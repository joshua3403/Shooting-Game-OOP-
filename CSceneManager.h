#pragma once
#include "stdafx.h"
#include "CBaseScene.h"
#include "CList(STL).h"

#define MAX_STAGE 2

enum class eState
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

class CSceneManager
{
private:
	CBaseScene* pScene = nullptr;
	int _iStage;
	eState _State;
	static CSceneManager SceneManager;


	eState State;

private:

	CSceneManager() : _iStage(1), _State(eState::CREATETITLE)
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

	void ChangeScene(eState Scene);

	void Run();

	CBaseScene* GetScenePointer();

	// GameScene ��ü���� �÷��̾��� �¸� �÷��׸� Ȯ���ϰ� true�� �Ǹ� stage�� ���� ����
	void StageClear();

	// stage���� ��ȯ
	int GetStage();

	void Reset();
};