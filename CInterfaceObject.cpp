#include "stdafx.h"
#include "CInterfaceObject.h"

CInterfaceObject::~CInterfaceObject()
{
}

bool CInterfaceObject::Action()
{

	return false;
}

void CInterfaceObject::Render()
{
	InterfaceClear();
	cs_MoveCursor(0, dfSCREEN_HEIGHT);
	printf("HP : ");
	for (int i = 0; i < _iHp; ++i)
	{
		printf("¢½");
	}
	cs_MoveCursor(0, dfSCREEN_HEIGHT + 1);
	printf("Damage : %d", _iDamage);
}

void CInterfaceObject::UpdateHp(int hp)
{
	this->_iHp = hp;
}

void CInterfaceObject::InterfaceClear()
{
	cs_MoveCursor(0, dfSCREEN_HEIGHT);
	printf("                   ");
	cs_MoveCursor(0, dfSCREEN_HEIGHT + 1);
	printf("                   ");

}
