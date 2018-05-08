//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Ability.h"
#include "Movement.h"
#include "CommonTooltips.h"

class MovementEnhanced : public Movement
{
public:
    MovementEnhanced()
    {
        costEN = 1;
        name = "Enhanced Movement";
        iconPath = "icons/MovementEnhanced.png";
        description = "<b><u>Enhanced Movement</u> ( 0.5 EN per tile )</b><br><br>"
            "Move to a different tile.<br>"
            MOVEMENT_TOOLTIP;
    }

protected:
	void calculateCost() override
    {
		calculatedCost = ceil((int(std::distance(calculatedPath.begin(), calculatedPath.end())) - 1) * costEN * 0.5f - 0.001f);
    }
};
