#include "stdafx.h"
#include "CGameScene.h"
#include "CPlayerObejct.h"
#include "CEnemyObject.h"



void CGameScene::Update()
{
	// �켱 ���۸� �����.
	Buffer_Clear();

	// Ű���� �Է��� �޴´�.
	GetKeyInput();
	for (const auto object : ObjectList)
	{
		object->Action();
		object->Render();
	}
}

void CGameScene::Sprite_Draw()
{
}

void CGameScene::GetKeyInput()
{
	bool bLeft = false;
	bool bRight = false;
	bool bUp = false;
	bool bDown = false;
	bool bCtrl = false;

	bLeft = GetAsyncKeyState(VK_LEFT) & 0x8000;
	bRight = GetAsyncKeyState(VK_RIGHT) & 0x8000;
	bUp = GetAsyncKeyState(VK_UP) & 0x8000;
	bDown = GetAsyncKeyState(VK_DOWN) & 0x8000;
	bCtrl = GetAsyncKeyState(VK_SPACE) & 0x8000;


	// �����ʰ� ������ ���ÿ�  ������� Ű�Է��� ���� �ʴ´�.
	if (!((bLeft == true) && (bRight == true)))
	{
		if (bLeft)
		{
			CPlayerObject::l_Player_Input.push_back(KeyInput::LEFT);
		}

		if (bRight)
		{
			CPlayerObject::l_Player_Input.push_back(KeyInput::RIGHT);
		}
	}

	// ���� �Ʒ��� ���ÿ�  ������� Ű�Է��� ���� �ʴ´�.
	if (!((bUp == true) && (bDown == true)))
	{
		if (bUp)
		{
			CPlayerObject::l_Player_Input.push_back(KeyInput::UP);
		}

		if (bDown)
		{
			CPlayerObject::l_Player_Input.push_back(KeyInput::DOWN);
		}
	}

	// ����Ű�� ������
	if (bCtrl)
	{
		CPlayerObject::l_Player_Input.push_back(KeyInput::ATTACK);
	}
}

void CGameScene::CreateEnemy(int iStageIndex)
{
	FILE* stage_file;
	switch (iStageIndex)
	{
	case 0:
		stage_file = fopen("Stage1.txt", "rb");
		break;
	case 1:
		stage_file = fopen("Stage2.txt", "rb");
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

		char Display;

		switch (Type)
		{
		case EnemyType::NORMAL1:
			Display = '@';
			break;
		case EnemyType::BOSS:
			Display = 'Z';
			break;
		}

		ObjectList.push_back(new CEnemyClass(this, eObjectType::ENEMY, PositionX, PositionY, Hp, Damage, Display, Type));


		if (buff == NULL)
			continue;
	}

}
