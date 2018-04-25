//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Ability.h"
#include <vector>

class Movement : public Ability
{
	std::vector<Field*> calculatedPath;
	int calculatedCost = 0;
public:
	Movement();
	void Effect(Board* board, Unit* abilityUser, Field* target) override;
	bool CanUse(Board* board, Unit* abilityUser, Field* target) override;
};
