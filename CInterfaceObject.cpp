#include "stdafx.h"
#include "CInterfaceObject.h"

bool CInterfaceObject::Action()
{

	return false;
}

void CInterfaceObject::Render()
{
	InterfaceClear();
	cs_MoveCursor(0, dfSCREEN_HEIGHT);
	printf("HP : ");
	for (int i = 0; i < iHp; ++i)
	{
		printf("¢½");
	}
	cs_MoveCursor(0, dfSCREEN_HEIGHT + 1);
	printf("Damage : %d", iDamage);
}

void CInterfaceObject::UpdateHp(int hp)
{
	this->iHp = hp;
}

void CInterfaceObject::InterfaceClear()
{
	cs_MoveCursor(0, dfSCREEN_HEIGHT);
	printf("                   ");
	cs_MoveCursor(0, dfSCREEN_HEIGHT + 1);
	printf("                   ");

}
