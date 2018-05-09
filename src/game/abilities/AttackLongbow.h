//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "AttackLine.h"
#include "CommonTooltips.h"

class AttackLongbow : public AttackLine
{
public:
    AttackLongbow()
    {
        costEN = 5;
        damageNormal = 9;
        rangeMin = 2;
        rangeMax = 9;
        name = "Longbow Attack";
        iconPath = "icons/AttackLongbow.png";
        description = "<b><u>Longbow Attack</u> ( 5 EN ) Line 2-9</b><br><br>"
            "Deals 9 normal damage to the target.<br>"
            NORMAL_DAMAGE_TOOLTIP;
		aiTargetValue = 9;
		aiCanHurt = true;
		aiTargetMissingHpMod = 0.2f;
		aiTargetMissingEnMod = 0.8f;
		aiTargetRelativeEnMod = 0.0f;
    }
};
