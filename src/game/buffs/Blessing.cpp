//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
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