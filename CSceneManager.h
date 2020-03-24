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

	// GameScene 객체에서 플레이어의 승리 플래그를 확인하고 true가 되면 stage의 값을 증가
	void StageClear();

	// stage값을 반환
	int GetStage();

	void Reset();
};