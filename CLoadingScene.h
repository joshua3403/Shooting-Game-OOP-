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
	bool bLoadingSceneEnd;
public:

	CLoadingScene();

	~CLoadingScene();


	void Update();

	void PrintOne();

	void PrintTwo();

	void PrintThree();

	bool GetLoadingSceneEnd();

	void Sprite_Draw();
};