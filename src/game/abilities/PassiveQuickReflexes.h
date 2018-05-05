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

class PassiveQuickReflexes : public PassiveAbility
{
public:
    explicit PassiveQuickReflexes(Unit* unit)
    {
        name = "Quick Reflexes";
        iconPath = "icons/PassiveQuickReflexes.png";
        description = "<b><u>Quick Reflexes</u> ( passive )</b><br><br>"
            "Prevents 40% of all damage dealt to the ranger if it originated from a line attack.<br>";
        unit->IncreaseDamageReductionLine(0.4f);
    }
};
