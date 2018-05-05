//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Ability.h"

class SpecialSmite : public Ability
{
    static int const damageNormal = 2;
    static int const damageEN = 3;
    static int const rangeMin = 1;
    static int const rangeMax = 5;
public:
    SpecialSmite();
    bool Effect(Board* board, Unit* abilityUser, Field* target) override;
    bool CanUse(Board* board, Unit* abilityUser, Field* target) override;
    void OnSelected(Board* board, Unit* abilityUser) override;
    void SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField) override;
};
