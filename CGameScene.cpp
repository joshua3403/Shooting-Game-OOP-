#include "stdafx.h"
#include "CGameScene.h"
#include "CPlayerObejct.h"
#include "CEnemyObject.h"
#include "CBulletObject.h"
#include "CInterfaceObject.h"
#include "CPotionObject.h"


CGameScene::CGameScene(int stage) : iStageIndex(stage), iEnemyCount(0)
{
	cs_ClearScreen();
	// 게임씬 객체가 생성 될 때 플레이어 오브젝트 생성.
	ObjectList.push_back(new CPlayerObject(this));
	// 객체가 생성 될 때 처음 1 스테이지에 관련된 적들을 생성
	CreateEnemy(iStageIndex);
	// 인터페이스 오브젝트 생성
	CreateInterface();
	bPlayerWin = false;
	bEnemyWin = false;
	QueryPerformanceFrequency(&fFreq);
	QueryPerformanceCounter(&startShoot1);
	QueryPerformanceCounter(&startShoot2);
	QueryPerformanceCounter(&startShootBOSS);
}

void CGameScene::Update()
{
	// 일시정지(Enter)키가 눌리지 않았으면
	Buffer_Clear();

	GetKeyInput();

	if (this->bEnter)
	{
		PrintPause();
	}
	else
	{
		UpdateInterface();

		ObjectPlay();

		EnemyCreateBullet();

		BulletCollision();

		DeleteBullet();

		DeletePotion();

		PotionCollision();

		CheckPlayerWin();

		Sprite_Draw();

	}

}

void CGameScene::ObjectPlay()
{
	CList<CBaseObject*>::iterator itor = ObjectList.begin();
	while (true)
	{
		if (itor == ObjectList.end())
			break;

		(*itor)->Action();
		(*itor)->Render();
		itor++;
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


	for (CList<CBaseObject*>::iterator itor = ObjectList.begin(); itor != ObjectList.end(); ++itor)
	{
		if ((*itor)->GetObjectType() == eObjectType::PLAYER)
		{
			Player = dynamic_cast<CPlayerObject*>(*itor);
			break;
		}
	}

	// 함수의 이름과 내용이 일치하진 않지만 여기서 iPlayerHp의 값을 갱신한다.
	iPlayerHp = Player->GetHp();

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
		ObjectList.push_back(new CBulletObject(this, CBulletObject::eWhoShoot::PLAYER, eObjectType::BULLET, Player->GetObjectPosition().iX, Player->GetObjectPosition().iY-1, 1, Player->GetDamage()));
	}

	if (bReturn)
		this->bEnter = !(this->bEnter);

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

		ObjectList.push_back(new CEnemyClass(this, eObjectType::ENEMY, PositionX, PositionY, Hp, Damage, Display, Type, Time));
		iEnemyCount++;

		if (buff == NULL)
			continue;
	}

	fclose(stage_file);

}

void CGameScene::DeleteBullet()
{
	CList<CBaseObject*>::iterator itor = ObjectList.begin();
	while (true)
	{
		if (itor == ObjectList.end())
			break;

		if ((*itor)->GetObjectType() == eObjectType::BULLET)
		{
			if ((*itor)->GetObjectPosition().iY == 0 || (*itor)->GetObjectPosition().iY == dfSCREEN_HEIGHT - 1)
			{
				itor = ObjectList.erase(itor);
			}
			else
			{
				itor++;
			}

		}
		else
		{
			itor++;
		}
	}
}

void CGameScene::BulletCollision()
{
	CList<CBaseObject*>::iterator ObjectIter = ObjectList.begin();
	while (ObjectIter != ObjectList.end())
	{
		// 오브젝트 리스트에서 총알을 찾고
		if ((*ObjectIter)->GetObjectType() == eObjectType::BULLET)
		{
			CList<CBaseObject*>::iterator Enemy = ObjectList.begin();
			CList<CBaseObject*>::iterator Player = ObjectList.begin();
			CList<CBaseObject*>::iterator Interface = ObjectList.begin();
			// 누가 발사했느냐에 따라
			switch (dynamic_cast<CBulletObject*>(*ObjectIter)->GetWhoShoot())
			{
				// 플레이어가 발사했다면
				case CBulletObject::eWhoShoot::PLAYER:
					while (Enemy != ObjectList.end())
					{
						// 적을 찾아
						if ((*Enemy)->GetObjectType() == eObjectType::ENEMY)
						{
							// 총알과 적의 위치가 같다면
							if ((*Enemy)->GetObjectPosition().iX == (*ObjectIter)->GetObjectPosition().iX && (*Enemy)->GetObjectPosition().iY == (*ObjectIter)->GetObjectPosition().iY)
							{
								// 적은 데미지를 받고
								(*Enemy)->GetDamageFromObject((*ObjectIter)->GetDamage());
								// 총알은 파괴되고(ObjectIter가 erase내부에서 다음으로 이동됨)
								ObjectIter = ObjectList.erase(ObjectIter);
								// 적의 체력이 0이면
								if ((*Enemy)->GetHp() == 0)
								{
									srand((unsigned int)time(NULL));
									int chance = rand() % 10;
									if (chance <= 2)
										ObjectList.push_back(new CPotionObject(this, (*Enemy)->GetObjectPosition().iX, (*Enemy)->GetObjectPosition().iY));
									iEnemyCount--;
									Enemy = ObjectList.erase(Enemy);
								}
							}
							else
							{
								Enemy++;
							}
						}
						else
						{
							Enemy++;
						}
					}
					ObjectIter++;
					break;

				case CBulletObject::eWhoShoot::ENEMY:
					while (Player != ObjectList.end())
					{
						// 플레이어를 찾아
						if ((*Player)->GetObjectType() == eObjectType::PLAYER)
						{
							if ((*Player)->GetObjectPosition().iX == (*ObjectIter)->GetObjectPosition().iX && (*Player)->GetObjectPosition().iY == (*ObjectIter)->GetObjectPosition().iY)
							{
								(*Player)->GetDamageFromObject((*ObjectIter)->GetDamage());
								// 총알은 파괴되고(ObjectIter가 erase내부에서 다음으로 이동됨)
								ObjectIter = ObjectList.erase(ObjectIter);
								// 플레이어의 체력이 0이면
								if ((*Player)->GetHp() == 0)
								{
									bEnemyWin = true;
								}
							}
							else
							{
								Player++;
							}
						}
						else
						{
							Player++;
						}
					}
					ObjectIter++;
					break;					
				default:
					break;
			}
		}
		else
		{
			ObjectIter++;
		}
	}
}

void CGameScene::EnemyCreateBullet()
{
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);

	for (CList<CBaseObject*>::iterator Enemy = ObjectList.begin(); Enemy != ObjectList.end();++Enemy)
	{
		if ((*Enemy)->GetObjectType() == eObjectType::ENEMY)
		{
			// 적의 슈팅 시점과 지금 시점을 비교
			__int64 time = (now.QuadPart - dynamic_cast<CEnemyClass*>(*Enemy)->GetLARGEINTEGER().QuadPart) / fFreq.QuadPart;

			// 구한 시간이 적 객체 내부에 존재하는 발사 시간과 일치하면
			if (time >= dynamic_cast<CEnemyClass*>(*Enemy)->GetShootTime())
			{
				// 총알 생성
				ObjectList.push_back(new CBulletObject(this, CBulletObject::eWhoShoot::ENEMY, eObjectType::BULLET, (*Enemy)->GetObjectPosition().iX, (*Enemy)->GetObjectPosition().iY + 1, 1, (*Enemy)->GetDamage()));

				// 적 객체 내의 발사 시간을 초기화
				dynamic_cast<CEnemyClass*>(*Enemy)->SetLARGEINTEGER(now);
			}

		}

	}

}

void CGameScene::CheckPlayerWin()
{
	if (this->iEnemyCount == 0)
	{
		bPlayerWin = true;
	}
}

bool CGameScene::GetPlayerWin()
{
	return this->bPlayerWin;
}

bool CGameScene::GetEnemyWin()
{
	return this->bEnemyWin;
}

void CGameScene::PrintPause()
{
	cs_MoveCursor(0, 12);
	printf(Pause);
}

void CGameScene::CreateInterface()
{
	CList<CBaseObject*>::iterator itor = ObjectList.begin();
	while (true)
	{
		if (itor == ObjectList.end())
			break;

		if ((*itor)->GetObjectType() == eObjectType::PLAYER)
		{
			ObjectList.push_back(new CInterfaceObject(this, (*itor)->GetHp(), (*itor)->GetDamage()));
			break;
		}
	}
}

void CGameScene::DeletePotion()
{
	CList<CBaseObject*>::iterator itor = ObjectList.begin();
	while (true)
	{
		if (itor == ObjectList.end())
			break;

		if ((*itor)->GetObjectType() == eObjectType::POTION)
		{
			if ((*itor)->GetObjectPosition().iY == dfSCREEN_HEIGHT - 1)
				itor = ObjectList.erase(itor);
			else
			{
				itor++;
			}
		}
		else
		{
			itor++;
		}
	}
}

void CGameScene::PotionCollision()
{
	CList<CBaseObject*>::iterator potion = ObjectList.begin();
	CList<CBaseObject*>::iterator player = ObjectList.begin();
	while (true)
	{
		if (potion == ObjectList.end())
			break;

		if ((*potion)->GetObjectType() == eObjectType::POTION)
		{
			while (true)
			{
				if (player == ObjectList.end())
				{
					potion++;
					break;
				}

				if ((*player)->GetObjectType() == eObjectType::PLAYER)
				{
					if ((*potion)->GetObjectPosition().iX == (*player)->GetObjectPosition().iX && (*potion)->GetObjectPosition().iY == (*player)->GetObjectPosition().iY)
					{
						(*player)->GetDamageFromObject((*potion)->GetDamage() * (-1));
						potion = ObjectList.erase(potion);
					}
					else
					{
						player++;
					}
				}
				else
				{
					player++;
				}
			}
		}
		else
		{
			potion++;
		}
	}
}

void CGameScene::UpdateInterface()
{
	CList<CBaseObject*>::iterator Interface = ObjectList.begin();
	while (true)
	{
		if (Interface == ObjectList.end())
			break;

		if ((*Interface)->GetObjectType() == eObjectType::INTERFACEDISPLAY)
		{
			dynamic_cast<CInterfaceObject*>(*Interface)->UpdateHp(iPlayerHp);
			break;
		}
		else
		{
			Interface++;
		}
	}
}
