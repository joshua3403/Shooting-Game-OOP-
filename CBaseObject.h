#pragma once

// ��ü�� �Ӽ��� ������ ����ü
enum class e_ObjectType
{
	PLAYER = 0,
	ENEMY,
	BULLET,
	POTION,
	INTERFACEDISPLAY,
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
	e_ObjectType _ObjectType;

	// ������Ʈ�� ����(���)��ġ
	sObjectPosition s_RelativePosition;

	// ������Ʈ�� ��� ����
	bool _bIsAlive;

	// ������Ʈ�� ü��
	int _iHp;

	// ������Ʈ�� ���ݷ�
	int _iDamage;

	// ������Ʈ�� ȭ�� ��� ���
	char _cDisplay;

public:
	CBaseObject(e_ObjectType _ObjectType, int X, int Y, int Hp, int Damage, char Display)
	{
		this->_ObjectType = _ObjectType;
		s_RelativePosition.iX = X;
		s_RelativePosition.iY = Y;
		_bIsAlive = true;
		_iHp = Hp;
		_iDamage = Damage;
		_cDisplay = Display;
	}

	virtual ~CBaseObject();


	virtual bool Action() = 0;

	virtual void Render() = 0;

	// ������Ʈ�� Ÿ���� ��ȯ
	e_ObjectType GetObjectType();

	// ������Ʈ�� ��ġ ����ü�� ��ȯ
	sObjectPosition GetObjectPosition();

	// �������� ����
	void TakeDamage(int damage);

	// ������Ʈ�� �������� ��ȯ
	int GetDamage();

	// �������� �μ��� �޾� hp���� ����
	void GetDamageFromObject(int damage);

	// ������Ʈ�� ü���� ��ȯ
	int GetHp();
};