//----------------------------------------------//
//  Author: Pavel Hranáč (xhrana02)             //
//  School: Vysoké učení technické v Brně       //
//  Faculty: Fakulta informačních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "AttackLine.h"
#include "CommonTooltips.h"

class AttackCrossbow : public AttackLine
{
public:
    AttackCrossbow()
    {
        costEN = 7;
        damageNormal = 6;
        damageHP = 3;
        rangeMin = 2;
        rangeMax = 7;
        name = "Crossbow Attack";
        iconPath = "icons/AttackCrossbow.png";
        description = "<b><u>Crossbow Attack</u> ( 7 EN ) Line 2-7</b><br><br>"
            "Deals 3 HP and 6 normal damage to the target.<br>"
            HP_DAMAGE_TOOLTIP
            NORMAL_DAMAGE_TOOLTIP
            COMBINED_DAMAGE_TOOLTIP;
    }
};
