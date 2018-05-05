//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Blessing.h"
#include "Unit.h"


Blessing::Blessing()
{
    name = "Blessing";
    maxDuration = 3;
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