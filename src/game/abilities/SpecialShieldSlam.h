//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Ability.h"

class SpecialShieldSlam : public Ability
{
    static int const damageEN = 3;
	static int const damageNormal = 3;
	static int const stunDuration = 1;
public:
    SpecialShieldSlam();
    bool Effect(Board* board, Unit* abilityUser, Field* target) override;
    void OnSelected(Board* board, Unit* abilityUser) override;
    void SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField) override;

protected:
	void calculateViableTargets(Board* board, Unit* abilityUser) final;
};
