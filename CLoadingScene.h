#pragma once
#include "stdafx.h"
#include "CBaseScene.h"
#include "CSceneManager.h"

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
"                  �̵� : ȭ��ǥ Ű, ���� : Space Bar, �Ͻ����� : Enter             \0",
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
"                  �̵� : ȭ��ǥ Ű, ���� : Space Bar, �Ͻ����� : Enter             \0",
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
"                  �̵� : ȭ��ǥ Ű, ���� : Space Bar, �Ͻ����� : Enter             \0",
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
	int _Stage;
	char StageInfo[dfSCREEN_WIDTH];
	CSceneManager* _pSceneManager;
public:

	CLoadingScene(int stage, CSceneManager* SceneManager);

	~CLoadingScene();


	void Update();

	void PrintOne();

	void PrintTwo();

	void PrintThree();


	void Sprite_Draw();

	void PrintStageInfo();

};