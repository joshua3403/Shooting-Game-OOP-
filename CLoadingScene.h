#pragma once
#include "stdafx.h"
#include "CBaseScene.h"

class CLoadingScene : public CBaseScene
{
private:
	char One[dfSCREEN_HEIGHT][dfSCREEN_WIDTH] = {
"                                                                                  \0",
"                                                                                  \0",
"                                                                                  \0",
"                                       ==========                                 \0",
"                                       ====  ====                                 \0",
"                                       == =  ====                                 \0",
"                                       ====  ====                                 \0",
"                                       ====  ====                                 \0",
"                                       ====  ====                                 \0",
"                                       ====  ====                                 \0",
"                                       ====  ====                                 \0",
"                                       ====  ====                                 \0",
"                                       ==      ==                                 \0",
"                                       ==========                                 \0",
"                                                                                  \0",
"                                                                                  \0",
"                                                                                  \0",
"                  이동 : 화살표 키, 공격 : Space Bar, 일시정지 : Enter             \0",
"                                                                                   \0",
"                                                                                   \0",
"                                                                                   \0",
"                                                                                   \0",
"                                                                                   \0",
"                                                                                   \0",
"                                                                                   \0",
	};

	char Two[dfSCREEN_HEIGHT][dfSCREEN_WIDTH] = {
"                                                                                  \0",
"                                                                                  \0",
"                                                                                  \0",
"                                      ===========                                 \0",
"                                      ====   ====                                 \0",
"                                      ==   =   ==                                 \0",
"                                      =   ===   =                                 \0",
"                                      ======   ==                                 \0",
"                                      =====   ===                                 \0",
"                                      ====   ====                                 \0",
"                                      ===   =====                                 \0",
"                                      ==   ======                                 \0",
"                                      =        ==                                 \0",
"                                      ===========                                 \0",
"                                                                                  \0",
"                                                                                  \0",
"                                                                                  \0",
"                  이동 : 화살표 키, 공격 : Space Bar, 일시정지 : Enter             \0",
"                                                                                   \0",
"                                                                                   \0",
"                                                                                   \0",
"                                                                                   \0",
"                                                                                   \0",
"                                                                                   \0",
"                                                                                   \0",

	};

	char Three[dfSCREEN_HEIGHT][dfSCREEN_WIDTH] = {
"                                                                                   \0",
"                                                                                   \0",
"                                                                                   \0",
"                                      ===========                                  \0",
"                                      ====   ====                                  \0",
"                                      ==   =   ==                                  \0",
"                                      =   ===   =                                  \0",
"                                      ======   ==                                  \0",
"                                      ====    ===                                  \0",
"                                      ======   ==                                  \0",
"                                      =  ===    =                                  \0",
"                                      ==   =   ==                                  \0",
"                                      ====   ====                                  \0",
"                                      ===========                                  \0",
"                                                                                   \0",
"                                                                                   \0",
"                                                                                   \0",
"                  이동 : 화살표 키, 공격 : Space Bar, 일시정지 : Enter             \0",
"                                                                                   \0",
"                                                                                   \0",
"                                                                                   \0",
"                                                                                   \0",
"                                                                                   \0",
"                                                                                   \0",
"                                                                                   \0",

	};

	LARGE_INTEGER fFreq;
	LARGE_INTEGER start;
	int Stage;
	char StageInfo[dfSCREEN_WIDTH];
	bool bLoadingSceneEnd;
public:

	CLoadingScene(int stage);

	~CLoadingScene();


	void Update();

	void PrintOne();

	void PrintTwo();

	void PrintThree();

	// 로딩이 끝났음을 알리는 flag를 반환하는 함수
	bool GetLoadingSceneEnd();

	void Sprite_Draw();

	void PrintStageInfo();

};