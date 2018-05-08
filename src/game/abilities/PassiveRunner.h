//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "PassiveAbility.h"
#include "Unit.h"

/**
 * \brief Only for UI purposes. Actual gameplay difference is made by using MovementEnhanced instead of Movement.
 */
class PassiveRunner : public PassiveAbility
{
public:
    explicit PassiveRunner()
    {
        name = "Runner";
        iconPath = "icons/PassiveRunner.png";
        description = "<b><u>Runner</u> ( passive )</b><br><br>"
            "Scout's Movement costs only 0.5 EN per tile.<br>";
    }
};
