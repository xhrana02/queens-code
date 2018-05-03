//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Ability.h"

class AttackLine : public Ability
{
protected:
	int damageNormal = 0;
	int damageHP = 0;
	int damageEN = 0;
	int rangeMin = 0;
	int rangeMax = 0;
public:
	bool Effect(Board* board, Unit* abilityUser, Field* target) final;
	bool CanUse(Board* board, Unit* abilityUser, Field* target) final;
	void OnSelected(Board* board, Unit* abilityUser) final;
	void SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField) final;
};
