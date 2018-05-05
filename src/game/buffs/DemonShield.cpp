//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
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