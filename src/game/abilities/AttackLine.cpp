//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "AttackLine.h"
#include "Game.h"
#include "Field.h"
#include "Flash.h"
#include "Targetfinding.h"

using namespace glm;

bool AttackLine::Effect(Board* board, Unit* abilityUser, Field* target)
{
	if(CanUse(board, abilityUser, target))
	{
		abilityUser->ReduceEN(costEN);
		auto targetUnit = target->GetUnitOnField();
		targetUnit->TakeDamage(Line, damageNormal, damageHP, damageEN);

		if (!targetUnit->IsUnitAlive())
		{
			targetUnit->OnUnitDeath();
		}
		else
		{
			if(game->IsRealGame())
			{
				// ReSharper disable once CppNonReclaimedResourceAcquisition
				new Flash(game, target->GetUnitOnField(), vec4(1.0f, 0.0f, 0.0f, 1.0f), damageNormal + 1.5*damageHP + 0.75*damageEN);
			}
		}
		PanCameraToTarget(target);
		return true;
	}
	return false;
}

bool AttackLine::CanUse(Board* board, Unit* abilityUser, Field* target)
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

void AttackLine::OnSelected(Board* board, Unit* abilityUser)
{
	board->HalflightFields(Targetfinding::GetLineEnemyTargets(board, abilityUser, rangeMin, rangeMax, true));
}

void AttackLine::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
	board->HighlightField(hoveredField);
	if(CanUse(board, abilityUser, hoveredField))
	{
		abilityUser->ReduceTheoreticalEN(costEN);
		hoveredField->GetUnitOnField()->TakeTheoreticalDamage(Line, damageNormal, damageHP, damageEN);
	}
}
