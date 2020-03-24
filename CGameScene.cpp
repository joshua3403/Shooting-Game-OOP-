
#include "stdafx.h"
#include "CGameScene.h"
#include "CPlayerObejct.h"
#include "CBulletObject.h"
#include "CEnemyObject.h"
#include "CInterfaceObject.h"
#include "CPotionObject.h"



CGameScene::CGameScene(CSceneManager* SceneManager ,int stage) : _iStageIndex(stage), _iEnemyCount(0)
{

	cs_ClearScreen();
	// 게임씬 객체가 생성 될 때 플레이어 오브젝트 생성.
	ObjectList.push_back(new CPlayerObject(this));
	// 객체가 생성 될 때 처음 1 스테이지에 관련된 적들을 생성
	CreateEnemy(_iStageIndex);
	// 인터페이스 오브젝트 생성
	CreateInterface();
	pSceneManager = SceneManager;
	_bPlayerWin = false;
	_bEnemyWin = false;

}

void CGameScene::Update()
{
	Buffer_Clear();

	GetKeyInput();

	// 일시정지(Enter)키가 눌리지 않았으면
	if (_bEnter)
	{
		PrintPause();
	}
	else
	{
		UpdateInterface();

		ObjectPlay();

		Sprite_Draw();

		ChangeScenePlayerLose();

		CheckStageClear();
	}

}

void CGameScene::ObjectPlay()
{

	for (std::list<CBaseObject*>::iterator itor = ObjectList.begin(); itor != ObjectList.end(); ++itor)
	{
		(*itor)->Action();
	}

	for (std::list<CBaseObject*>::iterator itor = ObjectList.begin(); itor != ObjectList.end(); ++itor)
	{
		(*itor)->Render();
	}	
}

void CGameScene::Sprite_Draw()
{
	for (int i = 0; i < dfSCREEN_HEIGHT; ++i)
	{
		cs_MoveCursor(0, i);
		printf(ScreenBuffer[i]);
	}
}


void CGameScene::GetKeyInput()
{
	bool bLeft = false;
	bool bRight = false;
	bool bUp = false;
	bool bDown = false;
	bool bSpace = false;
	bool bReturn = false;

	CPlayerObject* Player = nullptr;


	for (std::list<CBaseObject*>::iterator itor = ObjectList.begin(); itor != ObjectList.end(); ++itor)
	{
		if ((*itor)->GetObjectType() == e_ObjectType::PLAYER)
		{
			Player = dynamic_cast<CPlayerObject*>(*itor);
			break;
		}
	}

	// 함수의 이름과 내용이 일치하진 않지만 여기서 iPlayerHp의 값을 갱신한다.
	_iPlayerHp = Player->GetHp();

	if (Player == nullptr)
	{
		return;
	}

	bLeft = GetAsyncKeyState(VK_LEFT) & 0x8000;
	bRight = GetAsyncKeyState(VK_RIGHT) & 0x8000;
	bUp = GetAsyncKeyState(VK_UP) & 0x8000;
	bDown = GetAsyncKeyState(VK_DOWN) & 0x8000;
	bSpace = GetAsyncKeyState(VK_SPACE) & 0x8000;
	bReturn = GetAsyncKeyState(VK_RETURN) & 0x8000;

	// 오른쪽과 왼쪽이 동시에  눌릴경우 키입력을 받지 않는다.
	if (!((bLeft == true) && (bRight == true)))
	{
		if (bLeft)
		{
			Player->l_Player_Input.push_back(static_cast<int>(KeyInput::LEFT));
		}

		if (bRight)
		{
			Player->l_Player_Input.push_back(static_cast<int>(KeyInput::RIGHT));
		}

	}

	// 위와 아래가 동시에  눌릴경우 키입력을 받지 않는다.
	if (!((bUp == true) && (bDown == true)))
	{
		if (bUp)
		{
			Player->l_Player_Input.push_back(static_cast<int>(KeyInput::UP));
		}

		if (bDown)
		{
			Player->l_Player_Input.push_back(static_cast<int>(KeyInput::DOWN));
		}

	}

	// 공격키가 눌리면
	if (bSpace)
	{
		Player->l_Player_Input.push_back(static_cast<int>(KeyInput::ATTACK));
		ObjectList.push_back(new CBulletObject(this, CBulletObject::eWhoShoot::PLAYER, e_ObjectType::BULLET, Player->GetObjectPosition().iX, Player->GetObjectPosition().iY-1, 1, Player->GetDamage()));
	}

	if (bReturn)
		_bEnter = !_bEnter;

}

void CGameScene::CreateEnemy(int iStageIndex)
{
	FILE* stage_file = nullptr;
	switch (iStageIndex)
	{
	case 1:
		stage_file = fopen("Stage1.txt", "r");
		break;
	case 2:
		stage_file = fopen("Stage2.txt", "r");
		break;
	}

	if (stage_file == nullptr)
	{
		std::cout << "Read data error! " << std::endl;
		return;
	}

	while (!feof(stage_file))
	{
		char temp[32];
		fgets(temp, sizeof(temp), stage_file);
		char* buff = strtok(temp, " ");

		EnemyType Type = static_cast<EnemyType>(atoi(buff));

		buff = strtok(NULL, " ");

		int PositionX = atoi(buff);

		buff = strtok(NULL, " ");

		int PositionY = atoi(buff);

		buff = strtok(NULL, " ");

		int Hp = atoi(buff);

		buff = strtok(NULL, " ");

		int Damage = atoi(buff);

		buff = strtok(NULL, " ");
		
		int Time = atoi(buff);

		char Display;

		switch (Type)
		{
		case EnemyType::NORMAL1:
			Display = '@';
			break;
		case EnemyType::BOSS:
			Display = 'H';
			break;
		}

		ObjectList.push_back(new CEnemyClass(this, e_ObjectType::ENEMY, PositionX, PositionY, Hp, Damage, Display, Type, Time));
		_iEnemyCount++;

		if (buff == NULL)
			continue;
	}

	fclose(stage_file);

}

void CGameScene::GetEnemyDelete(void* enemy)
{
	std::list<CBaseObject*>::iterator it = ObjectList.begin();
	for (; it != ObjectList.end(); it++)
	{
		if ((*it) == (CEnemyClass*)enemy)
		{
			delete (*it);
			_iEnemyCount--;
			it = ObjectList.erase(it);
		}

	}
}

void CGameScene::GetBulletDelete(void* bullet)
{
	std::list<CBaseObject*>::iterator it = ObjectList.begin();
	for (; it != ObjectList.end(); it++)
	{
		if ((*it) == (CBulletObject*)bullet)
		{
			delete (*it);
			it = ObjectList.erase(it);
		}

	}
}

void CGameScene::GetPotionDelete(void* potion)
{
	std::list<CBaseObject*>::iterator it = ObjectList.begin();
	for (; it != ObjectList.end(); it++)
	{
		if ((*it) == (CPotionObject*)potion)
		{
			delete (*it);
			it = ObjectList.erase(it);
		}

	}
}

void CGameScene::GetPlayerLose()
{
	_bEnemyWin = true;
}

void CGameScene::ChangeScenePlayerLose()
{
	if (_bEnemyWin)
	{
		pSceneManager->ChangeScene(eState::CREATEDIE);
	}
}

void CGameScene::CheckStageClear()
{
	if (_iEnemyCount == 0)
	{
		pSceneManager->StageClear();
	}
}




void CGameScene::PrintPause()
{
	cs_MoveCursor(0, 12);
	printf(Pause);
}

void CGameScene::CreateInterface()
{
	std::list<CBaseObject*>::iterator itor = ObjectList.begin();
	while (true)
	{
		if (itor == ObjectList.end())
			break;

		if ((*itor)->GetObjectType() == e_ObjectType::PLAYER)
		{
			ObjectList.push_back(new CInterfaceObject(this, (*itor)->GetHp(), (*itor)->GetDamage()));
			break;
		}
	}
}

void CGameScene::UpdateInterface()
{
	std::list<CBaseObject*>::iterator Interface = ObjectList.begin();
	while (true)
	{
		if (Interface == ObjectList.end())
			break;

		if ((*Interface)->GetObjectType() == e_ObjectType::INTERFACEDISPLAY)
		{
			dynamic_cast<CInterfaceObject*>(*Interface)->UpdateHp(_iPlayerHp);
			break;
		}
		else
		{
			Interface++;
		}
	}
}

