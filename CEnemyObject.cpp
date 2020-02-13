#include "stdafx.h"
#include "CEnemyObject.h"

bool CEnemyClass::Action()
{
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);
	__int64 time = start.QuadPart - now.QuadPart / fFreq.QuadPart;

	if (this->etype == EnemyType::NORMAL1)
	{
		if (time >= 2)
		{
			// ���� �ð� ����� �ʱ�ȭ

			// TODO �ð��� ���� �ҷ��� ��������� ��
			QueryPerformanceCounter(&start);
			this->s_RelativePosition.iX += MAX_MOVE_RANGE1;
		}

	}
	else if (this->etype == EnemyType::BOSS)
	{
		if (time >= 3)
		{
			// ���� �ð� ����� �ʱ�ȭ

			// TODO �ð��� ���� �ҷ��� ��������� ��
			QueryPerformanceCounter(&start);
			this->s_RelativePosition.iX += MAX_MOVE_RANGE2;
		}
	}

	if (this->s_RelativePosition.iX < 0)
		this->s_RelativePosition.iX += dfSCREEN_WIDTH - 2;

	if (this->s_RelativePosition.iX > dfSCREEN_WIDTH - 2)
		this->s_RelativePosition.iX -= dfSCREEN_WIDTH - 2;

	return true;
}

void CEnemyClass::Render()
{
	if (this->bIsAlive)
	{
		pGameScene->Buffer_Clear[this->s_RelativePosition.iY][this->s_RelativePosition.iX] = this->iHp + '0';
	}
}
