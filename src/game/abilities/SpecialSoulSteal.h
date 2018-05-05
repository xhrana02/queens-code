//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Ability.h"

class SpecialSoulSteal : public Ability
{
protected:
    static int const damageHP = 6;
public:
    SpecialSoulSteal();
    bool Effect(Board* board, Unit* abilityUser, Field* target) final;
    bool CanUse(Board* board, Unit* abilityUser, Field* target) final;
    void OnSelected(Board* board, Unit* abilityUser) final;
    void SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField) final;
};
