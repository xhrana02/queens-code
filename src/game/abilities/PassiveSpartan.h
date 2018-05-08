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

class PassiveSpartan : public PassiveAbility
{
public:
    explicit PassiveSpartan(Unit* unit)
    {
        name = "Spartan";
        iconPath = "icons/PassiveSpartan.png";
		description = "<b><u>Spartan</u> ( passive )</b><br><br>"
			"When an enemy unit moves out of a neigbouring tile, the spearman deals 3 HP damage to it.<br>"
			ACTIVEPASSIVE_TOOLTIP
			HP_DAMAGE_TOOLTIP
			"<br><br>The Spearman also has bonus 1 Armor.<br>"
			ARMOR_TOOLTIP;
        unit->HasOpportunityAttack = true;
        unit->DamageOpportunityAttack = 3;
		unit->IncreaseArmor(1);
    }
};