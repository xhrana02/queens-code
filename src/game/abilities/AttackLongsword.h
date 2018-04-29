//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Ability.h"
#include <vector>

class AttackLongsword : public Ability
{
	int normalDamage = 9;
public:
	AttackLongsword();
	bool Effect(Board* board, Unit* abilityUser, Field* target) override;
	bool CanUse(Board* board, Unit* abilityUser, Field* target) override;
	void OnSelected(Board* board, Unit* abilityUser) override;
private:
	static std::vector<Field*> calculateViableTargets(Board* board, Unit* abilityUser);
};
