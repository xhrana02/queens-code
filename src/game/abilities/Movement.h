//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Ability.h"
#include <forward_list>

class Movement : public Ability
{
protected:
    std::forward_list<Field*> calculatedPath;
    int calculatedCost = 0;
public:
    Movement();
    bool Effect(Board* board, Unit* abilityUser, Field* target) override;
    bool CanUse(Board* board, Unit* abilityUser, Field* target) override;
    void OnSelected(Board* board, Unit* abilityUser) override;
    void SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField) override;

protected:
	void calculateViableTargets(Board* board, Unit* abilityUser) final;
	virtual void calculateCost();
};
