//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "PassiveAbility.h"
#include "CommonTooltips.h"
#include "Unit.h"

class PassiveOpportunityAttack : public PassiveAbility
{
public:
    explicit PassiveOpportunityAttack(Unit* unit)
    {
        name = "Opportunity Attack";
        iconPath = "icons/PassiveOpportunityAttack.png";
        description = "<b><u>Opportunity Attack</u> ( passive )</b><br><br>"
            "When an enemy unit moves out of a neigbouring tile, the spearman deals 3 HP damage to it.<br>"
            ACTIVEPASSIVE_TOOLTIP
            HP_DAMAGE_TOOLTIP;
        unit->HasOpportunityAttack = true;
        unit->DamageOpportunityAttack = 3;
    }
};