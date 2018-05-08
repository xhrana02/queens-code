//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "AttackMelee.h"
#include "CommonTooltips.h"

class AttackWarhammer : public AttackMelee
{
public:
    AttackWarhammer()
    {
        costEN = 5;
        damageNormal = 5;
        damageHP = 4;
        name = "Warhammer Attack";
        iconPath = "icons/AttackWarhammer.png";
        description = "<b><u>Warhammer Attack</u> ( 5 EN ) Melee</b><br><br>"
            "Deals 4 HP and 5 normal damage to the target.<br>"
            HP_DAMAGE_TOOLTIP
            NORMAL_DAMAGE_TOOLTIP
            COMBINED_DAMAGE_TOOLTIP;
		aiTargetValue = 17;
		aiTargetMissingHpMod = 0.4f;
		aiTargetMissingEnMod = 0.5f;
		aiTargetRelativeEnMod = 0.0f;
    }
};
