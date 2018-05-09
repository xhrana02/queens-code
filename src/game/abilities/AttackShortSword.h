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
        costEN = 2;
        damageNormal = 8;
        name = "Short Sword Attack";
        iconPath = "icons/AttackShortSword.png";
        description = "<b><u>Short Sword Attack</u> ( 2 EN ) Melee</b><br><br>"
            "Deals 8 normal damage to the target.<br>"
            NORMAL_DAMAGE_TOOLTIP;
		aiTargetValue = 20;
		aiCanHurt = true;
		aiTargetMissingHpMod = 0.2f;
		aiTargetMissingEnMod = 0.8f;
		aiTargetRelativeEnMod = 0.0f;
    }
};
