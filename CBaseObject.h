#pragma once

// 객체의 속성을 구분할 열거체
enum class e_ObjectType
{
	PLAYER = 0,
	ENEMY,
	BULLET,
	POTION,
	INTERFACEDISPLAY,
};

// 객체의 위치를 나타내는 구초체
struct sObjectPosition
{
	int iX;
	int iY;
};


class CBaseObject
{

protected:
	// 오브젝트 속성
	e_ObjectType _ObjectType;

	// 오브젝트의 현재(상대)위치
	sObjectPosition s_RelativePosition;

	// 오브젝트의 사용 유무
	bool _bIsAlive;

	// 오브젝트의 체력
	int _iHp;

	// 오브젝트의 공격력
	int _iDamage;

	// 오브젝트의 화면 출력 모습
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

	// 오브젝트의 타입을 반환
	e_ObjectType GetObjectType();

	// 오브젝트의 위치 구조체를 반환
	sObjectPosition GetObjectPosition();

	// 데미지를 입음
	void TakeDamage(int damage);

	// 오브젝트의 데미지를 반환
	int GetDamage();

	// 데미지를 인수로 받아 hp에서 차감
	void GetDamageFromObject(int damage);

	// 오브젝트의 체력을 반환
	int GetHp();
};