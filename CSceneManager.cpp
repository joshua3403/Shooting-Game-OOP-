#include "stdafx.h"
#include "CSceneManager.h"

CSceneManager CSceneManager::SceneManager;

void CSceneManager::Run()
{
	pScene->Update();
}

void CSceneManager::ChangeScene(CBaseScene* Scene)
{
	if (pScene != nullptr)
		delete pScene;
	this->pScene = Scene;
}

CBaseScene* CSceneManager::GetScenePointer()
{
	return pScene;
}

void CSceneManager::PlayerWin()
{
	iStage++;
}

int CSceneManager::GetStage()
{
	return this->iStage;
}
