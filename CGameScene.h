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

	// 게임 씬의 로직이 실행되는 함수
	void Update();

	// 오브젝트 리스트를 순회하면서 오브젝트의 Action과 Render함수를 실행시킴
	void ObjectPlay();

	// 화면에 프린트 하는 함수
	void Sprite_Draw();

	// 키보드 입력을 받아 리스트에 삽입하는 함수
	void GetKeyInput();

	// 스테이지의 정보를 받아 해당 적들을 생성하는 함수
	void CreateEnemy(int iStageIndex);

	// 적 오브젝트로부터 소멸을 전달받는 함수
	void GetEnemyDelete(void* enemy);

	// 총알의 소멸을 전달받는 함수
	void GetBulletDelete(void* bullet);

	// 포션의 소멸을 전달받는 함수
	void GetPotionDelete(void* potion);

	// 플레이어 오브젝트로부터 플레이어의 사망을 전달맏음
	void GetPlayerLose();

	// 씬 매니저에게 플레이어 패배 씬으로의 전환을 전달
	void ChangeScenePlayerLose();

	// 씬 매니저에게 플레이어 스테이지 클리어를 전달
	void CheckStageClear();

	// 일시 정지 화면 출력
	void PrintPause();

	// 인터페이스 오브젝트 생성
	void CreateInterface();

	// 인터페이스 오브젝트에게 플레이어 체력을 갱신시킴
	void UpdateInterface();


public:
	std::list<CBaseObject*> ObjectList;

};