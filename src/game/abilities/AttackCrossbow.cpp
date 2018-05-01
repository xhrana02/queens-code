//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "AttackCrossbow.h"
#include "Game.h"
#include "Field.h"
#include "Flash.h"
#include "Targetfinding.h"
#include "CommonTooltips.h"

using namespace glm;

AttackCrossbow::AttackCrossbow()
{
	costEN = 9;
	name = "Crossbow Attack";
	iconPath = "icons/AttackCrossbow.png";
	description = "<b><u>Crossbow Attack</u> ( 9 EN ) Line 2-8</b><br><br>"
		"Deals 11 normal damage to the target.<br><br>"
		NORMAL_DAMAGE_TOOLTIP;
}

bool AttackCrossbow::Effect(Board* board, Unit* abilityUser, Field* target)
{
	if(CanUse(board, abilityUser, target))
	{
		abilityUser->ReduceEN(costEN);
		auto targetUnit = target->GetUnitOnField();
		targetUnit->TakeDamage(normalDamage);

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
					new Flash(game, target->GetUnitOnField(), vec4(1.0f, 0.0f, 0.0f, 1.0f), normalDamage);
				}
			}
		}
		return true;
	}
	return false;
}

bool AttackCrossbow::CanUse(Board* board, Unit* abilityUser, Field* target)
{
	if (target == nullptr)
	{
		return false;
	}

	auto viableTargets = Targetfinding::GetLineEnemyTargets(board, abilityUser, rangeMin, rangeMax);
	for (auto viableTarget : viableTargets)
	{
		if (target == viableTarget)
		{
			return true;
		}
	}
	return false;
}

void AttackCrossbow::OnSelected(Board* board, Unit* abilityUser)
{
	board->HalflightFields(Targetfinding::GetLineEnemyTargets(board, abilityUser, rangeMin, rangeMax, true));
}

void AttackCrossbow::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
	board->HighlightField(hoveredField);
	if(CanUse(board, abilityUser, hoveredField))
	{
		abilityUser->ReduceTheoreticalEN(costEN);
		hoveredField->GetUnitOnField()->TakeTheoreticalDamage(normalDamage);
	}
}
