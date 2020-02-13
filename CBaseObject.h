#pragma once

// ��ü�� �Ӽ��� ������ ����ü
enum eObjectType
{
	PLAYER = 0,
	ENEMY,
	BULLET
};

// ��ü�� ��ġ�� ��Ÿ���� ����ü
struct sObjectPosition
{
	int iX;
	int iY;
};


class CBaseObject
{
protected:
	// ������Ʈ �Ӽ�
	eObjectType ObjectType;

	// ������Ʈ�� ����(���)��ġ
	sObjectPosition s_RelativePosition;

	// ������Ʈ�� ��� ����
	bool bIsAlive;

	// ������Ʈ�� ü��
	int iHp;

	// ������Ʈ�� ���ݷ�
	int iDamage;

	// ������Ʈ�� ȭ�� ��� ���
	char cDisplay;

public:
	CBaseObject(eObjectType ObjectType, int X, int Y, int Hp, int Damage, char Display)
	{
		this->ObjectType = ObjectType;
		s_RelativePosition.iX = X;
		s_RelativePosition.iY = Y;
		bIsAlive = true;
		iHp = Hp;
		iDamage = Damage;
		cDisplay = Display;
	}

	virtual ~CBaseObject()
	{
	};

	virtual bool Action()
	{

	};

	virtual void Render()
	{

	};
};