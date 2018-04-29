//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Movement.h"
#include "Game.h"
#include "Board.h"
#include "Field.h"
#include "Unit.h"
#include "Pathfinding.h"
#include "MovementAnimation.h"
#include "CommonTooltips.h"


Movement::Movement()
{
	costEN = 2;
	name = "Movement";
	iconPath = "icons/Movement.png";
	description = "<b><u>Movement</u> ( 2 EN per tile )</b><br><br>"
		"Move to a different tile. <br><br>"
		MOVEMENT_TOOLTIP;
}

bool Movement::Effect(Board* board, Unit* abilityUser, Field* target)
{
	if(CanUse(board, abilityUser, target))
	{
		abilityUser->ReduceEN(calculatedCost);
		target->MoveUnitToThisField(abilityUser);
		if(game != nullptr)
		{
			if(game->IsRealGame())
			{
				// ReSharper disable once CppNonReclaimedResourceAcquisition
				new MovementAnimation(game, abilityUser, calculatedPath);
			}
		}
		return true;
	}
	return false;
}

bool Movement::CanUse(Board* board, Unit* abilityUser, Field* target)
{
	if (target == nullptr)
	{
		return false;
	}
	if (target->IsFieldOccupied())
	{
		// can't enter occupied fields (includes origin = target scenario)
		return false;
	}

	calculatedPath = Pathfinding::FindPath(board, abilityUser->GetOccupiedField(), target);
	if (calculatedPath.empty())
	{
		return false;
	}
	calculatedCost = (int(distance(calculatedPath.begin(), calculatedPath.end())) - 1) * costEN;
	if (calculatedCost > abilityUser->GetCurrentEnergy())
	{
		return false;
	}
	return true;
}

void Movement::OnSelected(Board* board, Unit* abilityUser)
{
	auto viableTargets = Pathfinding::GetAllPossibleTargets(board, abilityUser->GetOccupiedField(), abilityUser->GetCurrentEnergy() / costEN);
	board->HalflightFields(viableTargets);
}



