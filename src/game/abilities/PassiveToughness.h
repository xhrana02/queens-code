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

class PassiveToughness : public PassiveAbility
{
public:
    explicit PassiveToughness(Unit* unit)
    {
        name = "Toughness";
        iconPath = "icons/PassiveToughness.png";
        description = "<b><u>Toughness</u> ( passive )</b><br><br>"
            "Regains bonus 1 HP when regenerating (1 HP and 3 EN total).<br>"
            REGENERATION_TOOLTIP;
        unit->IncreaseRegenerationHP(1);
    }
};
