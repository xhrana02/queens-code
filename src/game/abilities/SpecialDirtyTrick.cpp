//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "SpecialDirtyTrick.h"
#include "Game.h"
#include "Field.h"
#include "Flash.h"
#include "Targetfinding.h"
#include "CommonTooltips.h"

using namespace glm;

SpecialDirtyTrick::SpecialDirtyTrick()
{
	costEN = 1;
	name = "Dirty Trick";
	iconPath = "icons/SpecialDirtyTrick.png";
	description = "<b><u>Dirty Trick</u> ( 1 EN ) Melee</b><br><br>"
		"The target is stunned for 1 turn.<br>"
		STUN_TOOLTIP;
}

bool SpecialDirtyTrick::Effect(Board* board, Unit* abilityUser, Field* target)
{
	if(CanUse(board, abilityUser, target))
	{
		abilityUser->ReduceEN(costEN);
		auto targetUnit = target->GetUnitOnField();
		targetUnit->Stun(1);

		if(game->IsRealGame())
		{
			game->PanCameraToField(target);
			// ReSharper disable once CppNonReclaimedResourceAcquisition
			new Flash(game, target->GetUnitOnField(), vec4(1.0f, 1.0f, 0.0f, 1.0f), 5);
		}
		return true;
	}
	return false;
}

bool SpecialDirtyTrick::CanUse(Board* board, Unit* abilityUser, Field* target)
{
	if (target == nullptr)
	{
		return false;
	}

	auto viableTargets = Targetfinding::GetMeleeEnemyTargets(board, abilityUser);
	for (auto viableTarget : viableTargets)
	{
		if (target == viableTarget && !target->IsFieldFrozen())
		{
			return true;
		}
	}
	return false;
}

void SpecialDirtyTrick::OnSelected(Board* board, Unit* abilityUser)
{
	board->HalflightFields(Targetfinding::GetMeleeEnemyTargets(board, abilityUser, true));
}

void SpecialDirtyTrick::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
	board->HighlightField(hoveredField);
	if(CanUse(board, abilityUser, hoveredField))
	{
		abilityUser->ReduceTheoreticalEN(costEN);
	}
}
