//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "AttackLine.h"
#include "CommonTooltips.h"

class AttackShortbow : public AttackLine
{
public:
    AttackShortbow()
    {
        costEN = 3;
        damageNormal = 6;
        rangeMin = 2;
        rangeMax = 5;
        name = "Shortbow Attack";
        iconPath = "icons/AttackShortbow.png";
        description = "<b><u>Shortbow Attack</u> ( 5=3 EN ) Line 2-5</b><br><br>"
            "Deals 6 normal damage to the target.<br>"
            NORMAL_DAMAGE_TOOLTIP;
    }
};
