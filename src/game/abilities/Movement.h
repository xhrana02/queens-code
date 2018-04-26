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

	int animationProgress = 0;
	int animationGoal = 0;
	Unit* animationUnit = nullptr;
	std::vector<Field*> animationPath;
public:
	Movement();
	bool Effect(Board* board, Unit* abilityUser, Field* target) override;
	bool CanUse(Board* board, Unit* abilityUser, Field* target) override;
	bool LockedIteration() override;
};
