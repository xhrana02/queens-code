//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
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
        costEN = 4;
        damageNormal = 7;
        rangeMin = 2;
        rangeMax = 7;
        name = "Shortbow Attack";
        iconPath = "icons/AttackShortbow.png";
        description = "<b><u>Shortbow Attack</u> ( 4 EN ) Line 2-7</b><br><br>"
            "Deals 7 normal damage to the target.<br>"
            NORMAL_DAMAGE_TOOLTIP;
		aiTargetValue = 7;
		aiCanHurt = true;
		aiTargetMissingHpMod = 0.2f;
		aiTargetMissingEnMod = 0.8f;
		aiTargetRelativeEnMod = 0.0f;
    }
};
