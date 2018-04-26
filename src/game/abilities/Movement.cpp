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
			animationGoal = (calculatedPath.size() - 1) * 30;
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
	if (target->IsFieldOccupied())
	{
		return false;
	}
	calculatedPath = Pathfinding::FindPath(board, abilityUser->GetOccupiedField(), target);
	if (calculatedPath.empty())
	{
		return false;
	}
	calculatedCost = (calculatedPath.size() - 1) * costEN;
	if (calculatedCost > abilityUser->GetCurrentEnergy())
	{
		return false;
	}
	return true;
}

bool Movement::LockedIteration()
{
	auto fieldIndex = animationProgress / 30;
	auto fieldProgress = (animationProgress % 30) / 30.0f;
	auto fromField = animationPath[fieldIndex];
	auto toField = animationPath[fieldIndex + 1];
	auto fromPosX = fromField->GetX() - (fromField->GetBoard()->PlayableWidth() + 1) / 2.0f;
	auto fromPosY = fromField->GetY() - (fromField->GetBoard()->PlayableHeight() + 1) / 2.0f;
	auto toPosX = toField->GetX() - (toField->GetBoard()->PlayableWidth() + 1) / 2.0f;
	auto toPosY = toField->GetY() - (toField->GetBoard()->PlayableHeight() + 1) / 2.0f;
	auto posX = (fromPosX * (1 - fieldProgress) + toPosX * fieldProgress) / 2.0f;
	auto posY = (fromPosY * (1 - fieldProgress) + toPosY * fieldProgress) / 2.0f;
	animationUnit->SetCustomRenderingObjectPosition(posX, posY, 0.0f);

	animationProgress++;
	if (animationProgress == animationGoal)
	{
		animationPath.back->MoveUnitToThisField(animationUnit);
		return true;
	}
	return false;
}
