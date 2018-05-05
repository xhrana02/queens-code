//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "DemonShield.h"
#include "Unit.h"


DemonShield::DemonShield()
{
	name = "Demon Shield";
	maxDuration = 3;
}

void DemonShield::onEffectStart()
{
	affectedUnit->IncreaseArmor(armorIncrease);
}

void DemonShield::onEffectEnd()
{
	affectedUnit->DecreaseArmor(armorIncrease);
}