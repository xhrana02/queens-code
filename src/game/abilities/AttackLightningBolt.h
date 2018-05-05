//----------------------------------------------//
//  Author: Pavel Hranáč (xhrana02)             //
//  School: Vysoké učení technické v Brně       //
//  Faculty: Fakulta informačních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "AttackLine.h"
#include "CommonTooltips.h"

class AttackLightningBolt : public AttackLine
{
public:
    AttackLightningBolt()
    {
        costEN = 5;
        damageNormal = 5;
        damageEN = 7;
        rangeMin = 2;
        rangeMax = 8;
        name = "Lightning Bolt";
        iconPath = "icons/AttackLightningBolt.png";
        description = "<b><u>Lightning Bolt</u> ( 5 EN ) Line 2-8</b><br><br>"
            "Deals 7 EN and 5 normal damage to the target.<br>"
            EN_DAMAGE_TOOLTIP
            NORMAL_DAMAGE_TOOLTIP
            COMBINED_DAMAGE_TOOLTIP;
    }
};
