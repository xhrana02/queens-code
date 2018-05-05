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
        costEN = 6;
        damageNormal = 6;
        damageHP = 4;
        name = "Warhammer Attack";
        iconPath = "icons/AttackWarhammer.png";
        description = "<b><u>Warhammer Attack</u> ( 6 EN ) Melee</b><br><br>"
            "Deals 4 HP and 6 normal damage to the target.<br>"
            HP_DAMAGE_TOOLTIP
            NORMAL_DAMAGE_TOOLTIP
            COMBINED_DAMAGE_TOOLTIP;
    }
};
