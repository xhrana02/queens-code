//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Ability.h"

class PassiveThroneClaim : public Ability
{
public:
	PassiveThroneClaim();

	bool Effect(Board* board, Unit* abilityUser, Field* target) override;
	bool CanUse(Board* board, Unit* abilityUser, Field* target) override;
	bool LockedIteration() override;
	void OnSelected(Board* board, Unit* abilityUser) override;
};