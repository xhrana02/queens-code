//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Ability.h"

class SpecialCharge : public Ability
{
    static int const damageHP = 3;
    static int const rangeMin = 2;
    static int const rangeMax = 4;
    Field* fieldBehind = nullptr;
    Field* fieldInFront = nullptr;
public:
    SpecialCharge();
    bool Effect(Board* board, Unit* abilityUser, Field* target) override;
    void OnSelected(Board* board, Unit* abilityUser) override;
    void SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField) override;
    bool IsTargetPushable(Board* board, Unit* abilityUser, Unit* target);

protected:
	void calculateViableTargets(Board* board, Unit* abilityUser) final;
};
