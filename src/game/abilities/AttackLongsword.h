//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "AttackMelee.h"
#include "CommonTooltips.h"

class AttackLongsword : public AttackMelee
{
public:
    AttackLongsword()
    {
        costEN = 3;
        damageNormal = 9;
        name = "Longsword Attack";
        iconPath = "icons/AttackLongsword.png";
        description = "<b><u>Longsword Attack</u> ( 3 EN ) Melee</b><br><br>"
            "Deals 9 normal damage to the target.<br>"
            NORMAL_DAMAGE_TOOLTIP;
		aiTargetValue = 15;
		aiTargetMissingHpMod = 0.2f;
		aiTargetMissingEnMod = 0.8f;
		aiTargetRelativeEnMod = 0.0f;
    }
};
