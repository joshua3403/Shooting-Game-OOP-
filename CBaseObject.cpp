#include "stdafx.h"
#include "CBaseObject.h"

CBaseObject::~CBaseObject()
{
}

eObjectType CBaseObject::GetObjectType()
{
	return this->ObjectType;
}

sObjectPosition CBaseObject::GetObjectPosition()
{
	return this->s_RelativePosition;
}

int CBaseObject::GetDamage()
{
	return this->iDamage;
}

void CBaseObject::GetDamageFromObject(int damage)
{
	iHp -= damage;

	if (iHp <= 0)
		iHp = 0;
}

int CBaseObject::GetHp()
{
	return this->iHp;
}
