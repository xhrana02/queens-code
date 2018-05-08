//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Ability.h"
#include <vector>

class SpecialFireball : public Ability
{
    static int const damageNormal0 = 7;
    static int const damageNormal2 = 4;
    static int const rangeMin = 1;
    static int const rangeMax = 6;
    std::vector<Field*> areaOfEffectCandidates = std::vector<Field*>();
    std::vector<Field*> areaOfEffectTargets = std::vector<Field*>();
    static int const aoeRangeMin = 0;
    static int const aoeRangeMax = 2;
public:
    SpecialFireball();
    bool Effect(Board* board, Unit* abilityUser, Field* target) override;
    void OnSelected(Board* board, Unit* abilityUser) override;
    void SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField) override;

protected:
	void calculateViableTargets(Board* board, Unit* abilityUser) final;
    void CalculateAreaOfEffect(Board* board, Field* center);
};
