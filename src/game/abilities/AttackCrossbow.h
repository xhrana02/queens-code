//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Ability.h"

class AttackCrossbow : public Ability
{
	static int const normalDamage = 11;
	static int const rangeMin = 2;
	static int const rangeMax = 8;
public:
	AttackCrossbow();
	bool Effect(Board* board, Unit* abilityUser, Field* target) override;
	bool CanUse(Board* board, Unit* abilityUser, Field* target) override;
	void OnSelected(Board* board, Unit* abilityUser) override;
	void SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField) override;
};
