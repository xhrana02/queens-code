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
