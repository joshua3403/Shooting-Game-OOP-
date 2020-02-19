#include "stdafx.h"
#include "CSceneManager.h"
#include "CTitleScene.h"
#include "CLoadingScene.h"
#include "CGameScene.h"
//#include "My_New.h"

enum class eState
{
	CREATETITLE = 0,
	TITLE,
	CREATELOADING,
	LOADING,
	CREATEPLAY,
	PLAYING,
	PAUSE,
	CREATEDIE,
	DIE,
	WIN,
	ENDING
} State;


int main()
{
	cs_Initial();
	State = eState::CREATETITLE;
	CSceneManager* pSceneManager = CSceneManager::GetInstance();
	while (true)
	{
		switch (State)
		{
		case eState::CREATETITLE:
			pSceneManager->ChangeScene(new CTitleScene);
			State = eState::TITLE;
			break;

		case eState::TITLE:
			pSceneManager->Run();
			if (dynamic_cast<CTitleScene*>(pSceneManager->GetScenePointer())->GetEnterEntered())
				State = eState::CREATELOADING;
			break;

		case eState::CREATELOADING:
			pSceneManager->ChangeScene(new CLoadingScene);
			State = eState::LOADING;
			break;

		case eState::LOADING:
			pSceneManager->Run();
			if (dynamic_cast<CLoadingScene*>(pSceneManager->GetScenePointer())->GetLoadingSceneEnd())
				State = eState::CREATEPLAY;
			break;

		case eState::CREATEPLAY:
			pSceneManager->ChangeScene(new CGameScene(pSceneManager->GetStage()));
			State = eState::PLAYING;

		case eState::PLAYING:
			pSceneManager->Run();
			if (dynamic_cast<CGameScene*>(pSceneManager->GetScenePointer())->GetPlayerWin())
			{
				pSceneManager->PlayerWin();
				State = eState::CREATELOADING;
			}

			if (dynamic_cast<CGameScene*>(pSceneManager->GetScenePointer())->GetEnemyWin())
			{
				State = eState::CREATEDIE;
			}

			break;
		default:
			break;

		}

		Sleep(100);
	}


	return 0;
}