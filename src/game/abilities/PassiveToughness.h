//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
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
            "Regains bonus 2 HP when regenerating (2 HP and 4 EN total).<br>"
            REGENERATION_TOOLTIP;
        unit->IncreaseRegenerationHP(2);
    }
};
