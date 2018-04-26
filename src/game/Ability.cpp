//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Ability.h"
#include "Unit.h"
#include "Game.h"

bool Ability::CanAfford(Unit* abilityUser) const
{
	if (abilityUser->GetCurrentEnergy() < costEN)
	{
		return false;
	}
	if (abilityUser->GetCurrentHitPoints() < costHP)
	{
		return false;
	}
	return true;
}

bool Ability::LockGame()
{
	if (game != nullptr)
	{
		game->LockGame(this);
		return true;
	}
	return false;
}
