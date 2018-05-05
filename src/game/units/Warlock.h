//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Unit.h"
#include "Movement.h"
#include "SpecialFireball.h"
#include "SpecialDemonShield.h"
#include "SpecialSoulSteal.h"

class Warlock : public Unit
{
public:
    Warlock()
    {
        name = "Warlock";
        this->maximumHP = 16;
        currentHP = maximumHP;
        currentEN = maximumEN;
        abilities.push_back(std::make_shared<Movement>());
        abilities.push_back(std::make_shared<SpecialFireball>());
        abilities.push_back(std::make_shared<SpecialDemonShield>());
        abilities.push_back(std::make_shared<SpecialSoulSteal>());
    }
};
