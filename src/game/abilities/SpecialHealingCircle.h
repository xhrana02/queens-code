//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Ability.h"
#include <vector>

class SpecialHealingCircle : public Ability
{
    static int const healHP = 4;
    static int const healEN = 4;
    static int const aoeRangeMin = 1;
    static int const aoeRangeMax = 2;
public:
    SpecialHealingCircle();
    bool Effect(Board* board, Unit* abilityUser, Field* target) override;
    void OnSelected(Board* board, Unit* abilityUser) override;
    void SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField) override;

protected:
	void calculateViableTargets(Board* board, Unit* abilityUser) final;
};
