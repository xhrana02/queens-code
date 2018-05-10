//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "AttackMelee.h"
#include "CommonTooltips.h"

class AttackShortSword : public AttackMelee
{
public:
    AttackShortSword()
    {
        costEN = 3;
        damageNormal = 9;
        name = "Short Sword Attack";
        iconPath = "icons/AttackShortSword.png";
        description = "<b><u>Short Sword Attack</u> ( 3 EN ) Melee</b><br><br>"
            "Deals 9 normal damage to the target.<br>"
            NORMAL_DAMAGE_TOOLTIP;
		aiTargetValue = 30;
		aiCanHurt = true;
		aiTargetMissingHpMod = 0.2f;
		aiTargetMissingEnMod = 0.8f;
		aiTargetRelativeEnMod = 0.0f;
    }
};
