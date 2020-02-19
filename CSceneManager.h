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

	// GameScene 객체에서 플레이어의 승리 플래그를 확인하고 true가 되면 stage의 값을 증가
	void PlayerWin();

	// stage값을 반환
	int GetStage();
};