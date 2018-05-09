//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
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
