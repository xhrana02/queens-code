//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "SpecialHealingCircle.h"
#include "Game.h"
#include "Field.h"
#include "Flash.h"
#include "Targetfinding.h"
#include "CommonTooltips.h"

using namespace glm;

SpecialHealingCircle::SpecialHealingCircle()
{
	costEN = 7;
	name = "HealingCircle";
	iconPath = "icons/SpecialHealingCircle.png";
	description = "<b><u>HealingCircle</u> ( 7 EN )</b><br><br>"
		"Every allied unit in the range of 2 (excluding the priest) regains 4 HP and 4 EN.<br>";
}

bool SpecialHealingCircle::Effect(Board* board, Unit* abilityUser, Field* target)
{
	if(CanUse(board, abilityUser, target))
	{
		abilityUser->ReduceEN(costEN);

		for (auto aoeTarget : areaOfEffectTargets)
		{
			aoeTarget->GetUnitOnField()->Heal(healHP, healEN);

			if(game->IsRealGame())
			{
				// ReSharper disable once CppNonReclaimedResourceAcquisition
				new Flash(game, aoeTarget->GetUnitOnField(), vec4(0.0f, 1.0f, 0.0f, 0.5f), 3 + healHP + healEN);
			}
		}
		PanCameraToTarget(abilityUser->GetOccupiedField());
		return true;
	}
	return false;
}

bool SpecialHealingCircle::CanUse(Board* board, Unit* abilityUser, Field* target)
{
	if (target == nullptr)
	{
		return false;
	}

	CalculateAreaOfEffect(board, abilityUser);
	for (auto viableTarget : areaOfEffectTargets)
	{
		if (target == viableTarget)
		{
			return true;
		}
	}
	return false;
}

void SpecialHealingCircle::OnSelected(Board* board, Unit* abilityUser)
{
	CalculateAreaOfEffect(board, abilityUser);
	board->HalflightFields(areaOfEffectCandidates);
}

void SpecialHealingCircle::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
	if(CanUse(board, abilityUser, hoveredField))
	{
		board->HighlightFields(areaOfEffectTargets);
		abilityUser->ReduceTheoreticalEN(costEN);
		for (auto aoeTarget : areaOfEffectTargets)
		{
			aoeTarget->GetUnitOnField()->TheoreticalHeal(healHP, healEN);
		}
	}
}

void SpecialHealingCircle::CalculateAreaOfEffect(Board* board, Unit* abilityUser)
{
	areaOfEffectCandidates.clear();
	areaOfEffectCandidates = Targetfinding::GetIndirectAllyTargets(board, abilityUser, aoeRangeMin, aoeRangeMax);
	areaOfEffectTargets.clear();
	for (auto field : areaOfEffectCandidates)
	{
		if (field->GetUnitOnField() && !field->IsFieldFrozen())
		{
			areaOfEffectTargets.push_back(field);
		}
	}
}
