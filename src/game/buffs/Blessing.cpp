//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Blessing.h"
#include "Unit.h"


Blessing::Blessing(Unit* buffTarget)
	: Buff(buffTarget)
{
    id = blessing;
    maxDuration = 5;
}

void Blessing::onEffectStart()
{
    affectedUnit->IncreaseRegenerationEN(enRegenIncrease);
    affectedUnit->IncreaseArmor(armorIncrease);
}

void Blessing::onEffectEnd()
{
    affectedUnit->DecreaseRegenerationEN(enRegenIncrease);
    affectedUnit->DecreaseArmor(armorIncrease);
}