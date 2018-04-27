//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Ability.h"
#include <forward_list>

class Movement : public Ability
{
	std::forward_list<Field*> calculatedPath;
	int calculatedCost = 0;

	int animationProgress = 0;
	int animationGoal = 0;
	Unit* animationUnit = nullptr;
	std::forward_list<Field*> animationPath;
public:
	Movement();
	bool Effect(Board* board, Unit* abilityUser, Field* target) override;
	bool CanUse(Board* board, Unit* abilityUser, Field* target) override;
	bool LockedIteration() override;
	void OnSelected(Board* board, Unit* abilityUser) override;
};
