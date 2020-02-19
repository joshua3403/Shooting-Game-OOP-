#pragma once

// 객체의 속성을 구분할 열거체
enum eObjectType
{
	PLAYER = 0,
	ENEMY,
	BULLET
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
	eObjectType ObjectType;

	// 오브젝트의 현재(상대)위치
	sObjectPosition s_RelativePosition;

	// 오브젝트의 사용 유무
	bool bIsAlive;

	// 오브젝트의 체력
	int iHp;

	// 오브젝트의 공격력
	int iDamage;

	// 오브젝트의 화면 출력 모습
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

	virtual ~CBaseObject();


	virtual bool Action() = 0;

	virtual void Render() = 0;

	// 오브젝트의 타입을 반환
	eObjectType GetObjectType();

	// 오브젝트의 위치 구조체를 반환
	sObjectPosition GetObjectPosition();

	// 오브젝트의 데미지를 반환
	int GetDamage();

	// 데미지를 인수로 받아 hp에서 차감
	void GetDamageFromObject(int damage);

	// 오브젝트의 체력을 반환
	int GetHp();
};