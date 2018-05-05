//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "SpecialSmite.h"
#include "Game.h"
#include "Field.h"
#include "Flash.h"
#include "Targetfinding.h"
#include "CommonTooltips.h"

using namespace glm;

SpecialSmite::SpecialSmite()
{
	costEN = 3;
	name = "Smite";
	iconPath = "icons/SpecialSmite.png";
	description = "<b><u>Smite</u> ( 5 EN ) Indirect 1-5</b><br><br>"
		"The target takes 3 EN and 2 normal damage and is Stunned for 1 turn.<br>"
		STUN_TOOLTIP
		EN_DAMAGE_TOOLTIP;
}

bool SpecialSmite::Effect(Board* board, Unit* abilityUser, Field* target)
{
	if(CanUse(board, abilityUser, target))
	{
		abilityUser->ReduceEN(costEN);
		auto targetUnit = target->GetUnitOnField();
		targetUnit->Stun(1);
		targetUnit->TakeDamage(Melee, damageNormal, 0, damageEN);

		if (!targetUnit->IsUnitAlive())
		{
			targetUnit->OnUnitDeath();
		}
		else
		{
			if(game->IsRealGame())
			{
				// ReSharper disable once CppNonReclaimedResourceAcquisition
				new Flash(game, target->GetUnitOnField(), vec4(1.0f, 1.0f, 0.5f, 0.5f), 5 + damageNormal + 0.75 * damageEN);
			}
		}
		PanCameraToTarget(target);
		return true;
	}
	return false;
}

bool SpecialSmite::CanUse(Board* board, Unit* abilityUser, Field* target)
{
	if (target == nullptr)
	{
		return false;
	}

	auto viableTargets = Targetfinding::GetIndirectEnemyTargets(board, abilityUser, rangeMin, rangeMax);
	for (auto viableTarget : viableTargets)
	{
		if (target == viableTarget)
		{
			return true;
		}
	}
	return false;
}

void SpecialSmite::OnSelected(Board* board, Unit* abilityUser)
{
	board->HalflightFields(Targetfinding::GetIndirectEnemyTargets(board, abilityUser, rangeMin, rangeMax, true));
}

void SpecialSmite::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
	board->HighlightField(hoveredField);
	if(CanUse(board, abilityUser, hoveredField))
	{
		abilityUser->ReduceTheoreticalEN(costEN);
		hoveredField->GetUnitOnField()->TakeTheoreticalDamage(Melee, damageNormal, 0, damageEN);
	}
}
