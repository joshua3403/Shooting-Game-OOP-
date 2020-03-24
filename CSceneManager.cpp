#include "stdafx.h"
#include "CSceneManager.h"
#include "CTitleScene.h"
#include "CLoadingScene.h"
#include "CGameScene.h"
#include "CEndingScene.h"

CSceneManager CSceneManager::SceneManager;

void CSceneManager::ChangeScene(eState Scene)
{
	if (pScene != nullptr)
		delete pScene;
	_State = Scene;
}

void CSceneManager::Run()
{

	switch (_State)
	{
	case eState::CREATETITLE:
		pScene = new CTitleScene(this);
		_State = eState::TITLE;
		break;
	case eState::CREATELOADING:
		pScene = new CLoadingScene(_iStage, this);
		_State = eState::LOADING;
		break;
	case eState::CREATEPLAY:
		pScene = new CGameScene(this, _iStage);
		_State = eState::PLAYING;
		break;
	case eState::CREATEDIE:
		pScene = new CEndingScene(this);
		_State = eState::DIE;
		break;
	default:
		pScene->Update();
		break;
	}
}



CBaseScene* CSceneManager::GetScenePointer()
{
	return pScene;
}

void CSceneManager::StageClear()
{
	_iStage++;
}

int CSceneManager::GetStage()
{
	return _iStage;
}

void CSceneManager::Reset()
{
	_iStage = 1;
}
