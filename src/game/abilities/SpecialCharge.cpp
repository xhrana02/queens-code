//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "SpecialCharge.h"
#include "Game.h"
#include "Field.h"
#include "Flash.h"
#include "Targetfinding.h"
#include "CommonTooltips.h"
#include "MovementAnimation.h"

using namespace glm;

SpecialCharge::SpecialCharge()
{
	costEN = 8;
	name = "Charge";
	iconPath = "icons/SpecialCharge.png";
	description = "<b><u>Charge</u> ( 8 EN ) Line 2-4</b><br><br>"
		"Deals 3 HP damage to the target, pushes it 1 tile away and takes its place. If the tile behind the target is"
		"occupied, instead of pushing, the target takes 3 more HP damage and is stunned for 1 turn.<br>"
		STUN_TOOLTIP
		HP_DAMAGE_TOOLTIP;
}

bool SpecialCharge::Effect(Board* board, Unit* abilityUser, Field* target)
{
	if(CanUse(board, abilityUser, target))
	{
		abilityUser->ReduceEN(costEN);
		auto userField = abilityUser->GetOccupiedField();
		auto targetUnit = target->GetUnitOnField();

		if (!IsTargetPushable(board, abilityUser, targetUnit))
		{
			targetUnit->Stun(1);
			targetUnit->TakeDamage(Line, 0, 2*damageHP);
			fieldInFront->MoveUnitToThisField(abilityUser);
			if (!targetUnit->IsUnitAlive())
			{
				targetUnit->OnUnitDeath();
			}
			else
			{
				if(game != nullptr)
				{
					if(game->IsRealGame())
					{
						game->PanCameraToField(target);
						// ReSharper disable once CppNonReclaimedResourceAcquisition
						new MovementAnimation(game, abilityUser, std::forward_list<Field*>({userField,fieldInFront}), 6, false);
						// ReSharper disable once CppNonReclaimedResourceAcquisition
						new Flash(game, targetUnit, vec4(1.0f, 0.0f, 0.0f, 1.0f), 5 + 3*damageHP);
					}
				}
			}
		}
		else
		{
			targetUnit->TakeDamage(Line, 0, damageHP);
			fieldBehind->MoveUnitToThisField(targetUnit);
			target->MoveUnitToThisField(abilityUser);
			if(game != nullptr)
			{
				if(game->IsRealGame())
				{
					game->PanCameraToField(target);
					// ReSharper disable once CppNonReclaimedResourceAcquisition
					new Flash(game, targetUnit, vec4(1.0f, 0.5f, 0.0f, 1.0f), 5 + 1.5*damageHP, 5);
					// ReSharper disable once CppNonReclaimedResourceAcquisition
					new MovementAnimation(game, abilityUser, std::forward_list<Field*>({userField,target}), 6, false);
					// ReSharper disable once CppNonReclaimedResourceAcquisition
					new MovementAnimation(game, targetUnit, std::forward_list<Field*>({target,fieldBehind}), 8, false);
				}
			}
		}
		return true;
	}
	return false;
}

bool SpecialCharge::CanUse(Board* board, Unit* abilityUser, Field* target)
{
	if (target == nullptr)
	{
		return false;
	}

	auto candidates = Targetfinding::GetLineEnemyTargets(board, abilityUser, rangeMin, rangeMax);
	for (auto candidate : candidates)
	{
		if (candidate == target)
		{
			if (!IsTargetPushable(board, abilityUser, candidate->GetUnitOnField()))
			{
				if (fieldInFront->IsFieldOccupied())
				{
					return false;
				}
			}
			return true;
		}
	}
	return false;
}

void SpecialCharge::OnSelected(Board* board, Unit* abilityUser)
{
	auto candidates = Targetfinding::GetLineEnemyTargets(board, abilityUser, rangeMin, rangeMax, true);
	auto viableTargets = std::vector<Field*>();
	for (auto candidate : candidates)
	{
		auto unitCandidate = candidate->GetUnitOnField();
		if (unitCandidate != nullptr)
		{
			if (!IsTargetPushable(board, abilityUser, unitCandidate))
			{
				if (fieldInFront->IsFieldOccupied())
				{
					continue;
				}
			}
		}
		viableTargets.push_back(candidate);
	}
	board->HalflightFields(viableTargets);
}

void SpecialCharge::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
	board->HighlightField(hoveredField);
	if(CanUse(board, abilityUser, hoveredField))
	{
		abilityUser->ReduceTheoreticalEN(costEN);
		if (!IsTargetPushable(board, abilityUser, hoveredField->GetUnitOnField()))
		{
			hoveredField->GetUnitOnField()->TakeTheoreticalDamage(Line, 0, 2*damageHP);
		}
		else
		{
			hoveredField->GetUnitOnField()->TakeTheoreticalDamage(Line, 0, damageHP);
		}
	}
}

bool SpecialCharge::IsTargetPushable(Board* board, Unit* abilityUser, Unit* target)
{
	auto deltaX = target->GetOccupiedField()->GetX() - abilityUser->GetOccupiedField()->GetX();
	auto deltaY = target->GetOccupiedField()->GetY() - abilityUser->GetOccupiedField()->GetY();
	if (deltaX >  1) { deltaX =  1; }
	if (deltaX < -1) { deltaX = -1; }
	if (deltaY >  1) { deltaY =  1; }
	if (deltaY < -1) { deltaY = -1; }
	fieldInFront = board->GetField(
		target->GetOccupiedField()->GetX() - deltaX,
		target->GetOccupiedField()->GetY() - deltaY
	);
	fieldBehind = board->GetField(
		target->GetOccupiedField()->GetX() + deltaX,
		target->GetOccupiedField()->GetY() + deltaY
	);
	if (fieldBehind->IsFieldOccupied())
	{
		return false;
	}
	return true;
}
