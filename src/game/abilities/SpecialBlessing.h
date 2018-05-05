//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Ability.h"
#include <vector>

class SpecialBlessing : public Ability
{
	std::vector<Field*> areaOfEffectCandidates = std::vector<Field*>();
	std::vector<Field*> areaOfEffectTargets = std::vector<Field*>();
	static int const aoeRangeMin = 0;
	static int const aoeRangeMax = 2;
public:
	SpecialBlessing();
	bool Effect(Board* board, Unit* abilityUser, Field* target) override;
	bool CanUse(Board* board, Unit* abilityUser, Field* target) override;
	void OnSelected(Board* board, Unit* abilityUser) override;
	void SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField) override;
	void CalculateAreaOfEffect(Board* board, Unit* abilityUser);
};
