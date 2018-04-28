//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Blessing.h"
#include "Unit.h"


Blessing::Blessing()
{
	maxDuration = 3;
}

void Blessing::onEffectStart()
{
	affectedUnit->IncreaseRegenerationEN(1);
	affectedUnit->IncreaseArmor(1);
}

void Blessing::onEffectEnd()
{
	affectedUnit->DecreaseRegenerationEN(1);
	affectedUnit->DecreaseArmor(1);
}