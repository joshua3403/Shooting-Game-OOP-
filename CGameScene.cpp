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
	// ���Ӿ� ��ü�� ���� �� �� �÷��̾� ������Ʈ ����.
	ObjectList.push_back(new CPlayerObject(this));
	// ��ü�� ���� �� �� ó�� 1 ���������� ���õ� ������ ����
	CreateEnemy(iStageIndex);
	// �������̽� ������Ʈ ����
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
	// �Ͻ�����(Enter)Ű�� ������ �ʾ�����
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

	// �Լ��� �̸��� ������ ��ġ���� ������ ���⼭ iPlayerHp�� ���� �����Ѵ�.
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

	// �����ʰ� ������ ���ÿ�  ������� Ű�Է��� ���� �ʴ´�.
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

	// ���� �Ʒ��� ���ÿ�  ������� Ű�Է��� ���� �ʴ´�.
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

	// ����Ű�� ������
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
		// ������Ʈ ����Ʈ���� �Ѿ��� ã��
		if ((*ObjectIter)->GetObjectType() == eObjectType::BULLET)
		{
			CList<CBaseObject*>::iterator Enemy = ObjectList.begin();
			CList<CBaseObject*>::iterator Player = ObjectList.begin();
			CList<CBaseObject*>::iterator Interface = ObjectList.begin();
			// ���� �߻��ߴ��Ŀ� ����
			switch (dynamic_cast<CBulletObject*>(*ObjectIter)->GetWhoShoot())
			{
				// �÷��̾ �߻��ߴٸ�
				case CBulletObject::eWhoShoot::PLAYER:
					while (Enemy != ObjectList.end())
					{
						// ���� ã��
						if ((*Enemy)->GetObjectType() == eObjectType::ENEMY)
						{
							// �Ѿ˰� ���� ��ġ�� ���ٸ�
							if ((*Enemy)->GetObjectPosition().iX == (*ObjectIter)->GetObjectPosition().iX && (*Enemy)->GetObjectPosition().iY == (*ObjectIter)->GetObjectPosition().iY)
							{
								// ���� �������� �ް�
								(*Enemy)->GetDamageFromObject((*ObjectIter)->GetDamage());
								// �Ѿ��� �ı��ǰ�(ObjectIter�� erase���ο��� �������� �̵���)
								ObjectIter = ObjectList.erase(ObjectIter);
								// ���� ü���� 0�̸�
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
						// �÷��̾ ã��
						if ((*Player)->GetObjectType() == eObjectType::PLAYER)
						{
							if ((*Player)->GetObjectPosition().iX == (*ObjectIter)->GetObjectPosition().iX && (*Player)->GetObjectPosition().iY == (*ObjectIter)->GetObjectPosition().iY)
							{
								(*Player)->GetDamageFromObject((*ObjectIter)->GetDamage());
								// �Ѿ��� �ı��ǰ�(ObjectIter�� erase���ο��� �������� �̵���)
								ObjectIter = ObjectList.erase(ObjectIter);
								// �÷��̾��� ü���� 0�̸�
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
			// ���� ���� ������ ���� ������ ��
			__int64 time = (now.QuadPart - dynamic_cast<CEnemyClass*>(*Enemy)->GetLARGEINTEGER().QuadPart) / fFreq.QuadPart;

			// ���� �ð��� �� ��ü ���ο� �����ϴ� �߻� �ð��� ��ġ�ϸ�
			if (time >= dynamic_cast<CEnemyClass*>(*Enemy)->GetShootTime())
			{
				// �Ѿ� ����
				ObjectList.push_back(new CBulletObject(this, CBulletObject::eWhoShoot::ENEMY, eObjectType::BULLET, (*Enemy)->GetObjectPosition().iX, (*Enemy)->GetObjectPosition().iY + 1, 1, (*Enemy)->GetDamage()));

				// �� ��ü ���� �߻� �ð��� �ʱ�ȭ
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
