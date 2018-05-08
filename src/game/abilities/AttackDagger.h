//----------------------------------------------//
//  Author: Pavel Hranáč (xhrana02)             //
//  School: Vysoké učení technické v Brně       //
//  Faculty: Fakulta informačních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "AttackMelee.h"
#include "CommonTooltips.h"

class AttackDagger : public AttackMelee
{
public:
    AttackDagger()
    {
        costEN = 1;
        damageHP = 5;
        name = "Dagger Attack";
        iconPath = "icons/AttackDagger.png";
        description = "<b><u>Dagger Attack</u> ( 1 EN ) Melee</b><br><br>"
            "Deals 5 HP damage to the target.<br>"
            HP_DAMAGE_TOOLTIP;
		aiTargetValue = 20;
		aiTargetMissingHpMod = 0.5f;
		aiTargetMissingEnMod = 0.0f;
		aiTargetRelativeEnMod = 0.0f;
    }
};
