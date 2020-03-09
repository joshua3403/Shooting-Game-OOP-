#include "stdafx.h"
#include "CSceneManager.h"
#include "CTitleScene.h"
#include "CLoadingScene.h"
#include "CGameScene.h"
#include "CEndingScene.h"
#include "CStageClearScene.h"
#include "CWinScene.h"
//#include "New(Overriding).h"

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
			pSceneManager->ChangeScene(new CLoadingScene(pSceneManager->GetStage()));
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
				pSceneManager->StageClear();
				if (pSceneManager->GetStage() > MAX_STAGE)
					State = eState::CREATEWIN;
				else
					State = eState::CREATESTAGECLEAR;
			}

			if (dynamic_cast<CGameScene*>(pSceneManager->GetScenePointer())->GetEnemyWin())
			{
				State = eState::CREATEDIE;
			}
			break;

		case eState::CREATEDIE:
			pSceneManager->ChangeScene(new CEndingScene());
			State = eState::DIE;
			break;

		case eState::DIE:
			pSceneManager->Run();
			if (dynamic_cast<CEndingScene*>(pSceneManager->GetScenePointer())->GetEndingSceneEnd())
				State = eState::CREATETITLE;
			break;

		case eState::CREATESTAGECLEAR:
			pSceneManager->ChangeScene(new CStageClearScene);
			State = eState::STAGECLEAR;
			break;

		case eState::STAGECLEAR:
			pSceneManager->Run();
			if (dynamic_cast<CStageClearScene*>(pSceneManager->GetScenePointer())->GetStageClearEnd())
				State = eState::CREATELOADING;
			break;

		case eState::CREATEWIN:
			pSceneManager->ChangeScene(new CWinScene);
			State = eState::WIN;
			break;

		case eState::WIN:
			pSceneManager->Run();
			if (dynamic_cast<CWinScene*>(pSceneManager->GetScenePointer())->GetWindSceneEnd())
			{
				pSceneManager->Reset();
				State = eState::CREATETITLE;
			}
			break;
		default:
			break;

		}

		Sleep(100);
	}


	return 0;
}