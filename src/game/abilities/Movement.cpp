//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Movement.h"
#include "Board.h"
#include "Field.h"
#include "Unit.h"
#include "Pathfinding.h"


Movement::Movement()
{
	costEN = 2;
	name = "Movement";
	iconPath = "icons/Movement.png";
	description = "<b><u>Movement</u></b> ( 2 EN per tile )<br><br>"
		"Move to a different tile. <br><br>"
		"<i>Diagonal pathing is only possible if both neighbouring perpendicular tiles are also empty.</i>";
}

bool Movement::Effect(Board* board, Unit* abilityUser, Field* target)
{
	if(CanUse(board, abilityUser, target))
	{
		abilityUser->ReduceEN(calculatedCost);
		if(LockGame())
		{
			animationUnit = abilityUser;
			animationPath = calculatedPath;
			animationProgress = 0;
			// 30 iterations (frames) per tile
			animationGoal = (int(distance(calculatedPath.begin(), calculatedPath.end())) - 1) * 20;
		}
		else
		{
			target->MoveUnitToThisField(abilityUser);
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

bool Movement::LockedIteration()
{
	// Establish fromField and toField
	auto iterator = animationPath.begin();
	auto fieldIndex = animationProgress / 20;
	advance(iterator, fieldIndex);
	auto fromField = *iterator;
	advance(iterator, 1);
	auto toField = *iterator;

	// Get coordinates of these 2 fields
	auto fromPosX = fromField->GetX() - (fromField->GetBoard()->PlayableWidth() + 1) / 2.0f;
	auto fromPosY = fromField->GetY() - (fromField->GetBoard()->PlayableHeight() + 1) / 2.0f;
	auto toPosX = toField->GetX() - (toField->GetBoard()->PlayableWidth() + 1) / 2.0f;
	auto toPosY = toField->GetY() - (toField->GetBoard()->PlayableHeight() + 1) / 2.0f;

	// Position the unit model between them
	auto fieldProgress = (animationProgress % 20) / 20.0f;
	auto posX = fromPosX * (1 - fieldProgress) + toPosX * fieldProgress;
	auto posY = fromPosY * (1 - fieldProgress) + toPosY * fieldProgress;

	animationUnit->SetCustomRenderingObjectPosition(posX, posY, 0.0f);

	animationProgress++;
	if (animationProgress == animationGoal)
	{
		toField->MoveUnitToThisField(animationUnit);
		return true;
	}
	return false;
}

void Movement::OnSelected(Board* board, Unit* abilityUser)
{
	auto viableTargets = Pathfinding::GetAllPossibleTargets(board, abilityUser->GetOccupiedField(), abilityUser->GetCurrentEnergy() / costEN);
	board->HalflightFields(viableTargets);
}


