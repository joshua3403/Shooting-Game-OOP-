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
	LARGE_INTEGER fFreq;
	LARGE_INTEGER startShoot1;
	LARGE_INTEGER startShoot2;
	LARGE_INTEGER startShootBOSS;
public:

	CGameScene(int stage);


	~CGameScene()
	{
		ObjectList.clear();
	}

	// 게임 씬의 로직이 실행되는 함수
	void Update();

	// 화면에 프린트 하는 함수
	void Sprite_Draw();

	// 키보드 입력을 받아 리스트에 삽입하는 함수
	void GetKeyInput();

	// 스테이지의 정보를 받아 해당 적들을 생성하는 함수
	void CreateEnemy(int iStageIndex);

	// 화면의 범위를 벗어난 총알을 삭제하는 함수
	void DeleteBullet();

	// 움직이는 총알과 오브젝트의 충돌을 처리하는 함수
	void BulletCollision();

	// 적이 불렛을 생성하는 함수
	void EnemyCreateBullet();

	// 플레이어가 스테이지를 깼는지 확인하는 함수
	void CheckPlayerWin();

	// 플레이어 승리의 플래그를 반환
	bool GetPlayerWin();

	// 적의 승리 플래그를 반환
	bool GetEnemyWin();
	
};