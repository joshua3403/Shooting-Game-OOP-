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

	// �ε��� �������� �˸��� flag�� ��ȯ�ϴ� �Լ�
	bool GetLoadingSceneEnd();

	void Sprite_Draw();

	void PrintStageInfo();

};