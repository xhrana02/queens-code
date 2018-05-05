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

class PassiveMeditation : public PassiveAbility
{
public:
    explicit PassiveMeditation(Unit* unit)
    {
        name = "Meditation";
        iconPath = "icons/PassiveMeditation.png";
        description = "<b><u>Meditation</u> ( passive )</b><br><br>"
            "Regains bonus 2 EN when resting (1 HP and 5 EN total).<br>"
            REST_TOOLTIP;
        unit->IncreaseRestEN(2);
    }
};
