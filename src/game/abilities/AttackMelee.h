//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Ability.h"

class AttackMelee : public Ability
{
protected:
    int damageNormal = 0;
    int damageHP = 0;
    int damageEN = 0;
public:
    bool Effect(Board* board, Unit* abilityUser, Field* target) final;
    bool CanUse(Board* board, Unit* abilityUser, Field* target) final;
    void OnSelected(Board* board, Unit* abilityUser) final;
    void SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField) final;
};
