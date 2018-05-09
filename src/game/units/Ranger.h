//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Unit.h"
#include "Movement.h"
#include "AttackLongbow.h"
#include "AttackShortSword.h"
#include "PassiveQuickReflexes.h"

class Ranger : public Unit
{
public:
    Ranger()
    {
        name = "Ranger";
        this->maximumHP = 14;
        currentHP = maximumHP;
        currentEN = maximumEN;
        abilities.push_back(std::make_shared<Movement>());
        abilities.push_back(std::make_shared<AttackLongbow>());
        abilities.push_back(std::make_shared<AttackShortSword>());
        abilities.push_back(std::make_shared<PassiveQuickReflexes>(this));
    }
};
