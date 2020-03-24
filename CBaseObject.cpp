#include "stdafx.h"
#include "CBaseObject.h"

CBaseObject::~CBaseObject()
{
}

e_ObjectType CBaseObject::GetObjectType()
{
	return this->_ObjectType;
}


sObjectPosition CBaseObject::GetObjectPosition()
{
	return this->s_RelativePosition;
}

void CBaseObject::TakeDamage(int damage)
{
	_iHp -= damage;
}

int CBaseObject::GetDamage()
{
	return this->_iDamage;
}

void CBaseObject::GetDamageFromObject(int damage)
{
	_iHp -= damage;

	if (_iHp <= 0)
		_iHp = 0;
}

int CBaseObject::GetHp()
{
	return this->_iHp;
}
