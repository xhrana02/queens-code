//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
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
