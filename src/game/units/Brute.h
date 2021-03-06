//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Unit.h"
#include "Movement.h"
#include "AttackWarhammer.h"
#include "SpecialCharge.h"
#include "PassiveToughness.h"

class Brute : public Unit
{
public:
    Brute()
    {
        name = "Brute";
        this->maximumHP = 16;
        currentHP = maximumHP;
        currentEN = maximumEN;
        abilities.push_back(std::make_shared<Movement>());
        abilities.push_back(std::make_shared<AttackWarhammer>());
        abilities.push_back(std::make_shared<SpecialCharge>());
        abilities.push_back(std::make_shared<PassiveToughness>(this));
    }
};
