//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Ability.h"
#include <vector>

class SpecialHealingCircle : public Ability
{
    static int const healHP = 4;
    static int const healEN = 4;
    std::vector<Field*> areaOfEffectCandidates = std::vector<Field*>();
    std::vector<Field*> areaOfEffectTargets = std::vector<Field*>();
    static int const aoeRangeMin = 1;
    static int const aoeRangeMax = 2;
public:
    SpecialHealingCircle();
    bool Effect(Board* board, Unit* abilityUser, Field* target) override;
    bool CanUse(Board* board, Unit* abilityUser, Field* target) override;
    void OnSelected(Board* board, Unit* abilityUser) override;
    void SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField) override;
    void CalculateAreaOfEffect(Board* board, Unit* abilityUser);
};
