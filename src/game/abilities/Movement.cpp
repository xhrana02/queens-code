//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
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
#include "Flash.h"

using namespace glm;

Movement::Movement()
{
	costEN = 2;
	name = "Movement";
	iconPath = "icons/Movement.png";
	description = "<b><u>Movement</u> ( 2 EN per tile )</b><br><br>"
		"Move to a different tile.<br>"
		MOVEMENT_TOOLTIP;
}

bool Movement::Effect(Board* board, Unit* abilityUser, Field* target)
{
	if(CanUse(board, abilityUser, target))
	{
		abilityUser->ReduceEN(calculatedCost);
		for (auto neighbor : board->GetAllMeleeNeighborFields(abilityUser->GetOccupiedField()))
		{
			auto neighborUnit = neighbor->GetUnitOnField();
			if (neighborUnit != nullptr)
			{
				if (neighborUnit->HasOpportunityAttack && abilityUser->IsEnemy(neighborUnit) && !neighborUnit->IsStunned())
				{
					abilityUser->TakeDamage(Melee, 0, neighborUnit->DamageOpportunityAttack);
					
					if(game != nullptr)
					{
						if(game->IsRealGame())
						{
							// ReSharper disable once CppNonReclaimedResourceAcquisition
							new Flash(game, abilityUser, vec4(1.0f, 0.0f, 0.0f, 1.0f), 1.5*neighborUnit->DamageOpportunityAttack);
						}
					}
				}
			}
		}
		if (!abilityUser->IsUnitAlive())
		{
			abilityUser->OnUnitDeath();
		}
		else
		{
			target->MoveUnitToThisField(abilityUser);
			if (game != nullptr)
			{
				if (game->IsRealGame())
				{
					// ReSharper disable once CppNonReclaimedResourceAcquisition
					new MovementAnimation(game, abilityUser, calculatedPath);
				}
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
	calculatedCost = (int(std::distance(calculatedPath.begin(), calculatedPath.end())) - 1) * costEN;
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

void Movement::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
	board->HighlightField(hoveredField);
	if(CanUse(board, abilityUser, hoveredField))
	{
		abilityUser->ReduceTheoreticalEN(calculatedCost);
		for (auto neighbor : board->GetAllMeleeNeighborFields(abilityUser->GetOccupiedField()))
		{
			auto neighborUnit = neighbor->GetUnitOnField();
			if (neighborUnit != nullptr)
			{
				if (neighborUnit->HasOpportunityAttack && abilityUser->IsEnemy(neighborUnit) && !neighborUnit->IsStunned())
				{
					abilityUser->TakeTheoreticalDamage(Melee, 0, neighborUnit->DamageOpportunityAttack);
				}
			}
		}
	}
}



