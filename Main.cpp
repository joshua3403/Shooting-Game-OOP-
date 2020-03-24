#include "stdafx.h"
#include "CSceneManager.h"
#include "CTitleScene.h"
#include "CLoadingScene.h"
#include "CGameScene.h"
#include "CEndingScene.h"
#include "CStageClearScene.h"
#include "CWinScene.h"
//#include "My_new.h"



int main()
{
	timeBeginPeriod(1);
	srand(time(NULL));
	cs_Initial();
	CSceneManager* pSceneManager = CSceneManager::GetInstance();
	while (true)
	{
		pSceneManager->Run();

		Sleep(100);
	}


	return 0;
}