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
        description = "<b><u>Enhanced Movement</u> ( 1 EN per tile )</b><br><br>"
            "Move to a different tile.<br>"
            MOVEMENT_TOOLTIP;
    }
};
