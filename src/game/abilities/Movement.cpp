//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Movement.h"
#include "Pathfinding.h"


Movement::Movement()
{
	costEN = 2;
}

void Movement::Effect(Board* board, Unit* abilityUser, Field* target)
{
	// TEMPORARY
	if(CanUse(board, abilityUser, target))
	{
		abilityUser->ReduceEN(calculatedCost);
		target->MoveUnitToThisField(abilityUser);
	}
}

bool Movement::CanUse(Board* board, Unit* abilityUser, Field* target)
{
	if (target->IsFieldOccupied())
	{
		return false;
	}
	calculatedPath = Pathfinding::FindPath(board, abilityUser->GetOccupiedField(), target);
	if (calculatedPath.empty())
	{
		return false;
	}
	calculatedCost = int(calculatedPath.size()) * costEN;
	if (calculatedCost > abilityUser->GetCurrentEnergy())
	{
		return false;
	}
	return true;
}
