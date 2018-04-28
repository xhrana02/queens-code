//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "AttackLongsword.h"

AttackLongsword::AttackLongsword()
{
}

bool AttackLongsword::Effect(Board* board, Unit* abilityUser, Field* target)
{
	return false;
}

bool AttackLongsword::CanUse(Board* board, Unit* abilityUser, Field* target)
{
	return false;
}

bool AttackLongsword::LockedIteration()
{
	return false;
}

void AttackLongsword::OnSelected(Board* board, Unit* abilityUser)
{
}
