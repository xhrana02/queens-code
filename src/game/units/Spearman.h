//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Unit.h"
#include "Movement.h"
#include "AttackSpear.h"
#include "SpecialShieldSlam.h"
#include "PassiveOpportunityAttack.h"

class Spearman : public Unit
{
public:
    Spearman()
    {
        name = "Spearman";
        this->maximumHP = 18;
        currentHP = maximumHP;
        currentEN = maximumEN;
        abilities.push_back(std::make_shared<Movement>());
        abilities.push_back(std::make_shared<AttackSpear>());
        abilities.push_back(std::make_shared<SpecialShieldSlam>());
        abilities.push_back(std::make_shared<PassiveOpportunityAttack>(this));
    }
};
