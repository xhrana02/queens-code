//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "PassiveThroneClaim.h"

PassiveThroneClaim::PassiveThroneClaim()
{
	name = "Claim Throne";
	iconPath = "icons/PassiveThroneClaim.png";
	description = "<b><u>Claim Throne</u></b> ( passive )<br><br>"
		"When standing on the throne tile at the end of the turn,"
		" all enemy units become Restless for 1 turn.";
	isPassive = true;
}

bool PassiveThroneClaim::Effect(Board* board, Unit* abilityUser, Field* target)
{
	// IS PASSIVE
	return false;
}

bool PassiveThroneClaim::CanUse(Board* board, Unit* abilityUser, Field* target)
{
	// IS PASSIVE
	return false;
}

bool PassiveThroneClaim::LockedIteration()
{
	// IS PASSIVE
	return true;
}

void PassiveThroneClaim::OnSelected(Board* board, Unit* abilityUser)
{
	// IS PASSIVE
}
