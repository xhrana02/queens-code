//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "AttackLongsword.h"
#include "Game.h"
#include "Field.h"
#include "Flash.h"
#include "Targetfinding.h"
#include "CommonTooltips.h"

using namespace glm;

AttackLongsword::AttackLongsword()
{
	costEN = 4;
	name = "Longsword Attack";
	iconPath = "icons/AttackLongsword.png";
	description = "<b><u>Longsword Attack</u> ( 4 EN ) Melee</b><br><br>"
		"Deals 9 normal damage to the target.<br>"
		NORMAL_DAMAGE_TOOLTIP;
}

bool AttackLongsword::Effect(Board* board, Unit* abilityUser, Field* target)
{
	if(CanUse(board, abilityUser, target))
	{
		abilityUser->ReduceEN(costEN);
		auto targetUnit = target->GetUnitOnField();
		targetUnit->TakeDamage(damageNormal);

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
					new Flash(game, target->GetUnitOnField(), vec4(1.0f, 0.0f, 0.0f, 1.0f), damageNormal);
				}
			}
		}
		return true;
	}
	return false;
}

bool AttackLongsword::CanUse(Board* board, Unit* abilityUser, Field* target)
{
	if (target == nullptr)
	{
		return false;
	}

	auto viableTargets = Targetfinding::GetMeleeEnemyTargets(board, abilityUser);
	for (auto viableTarget : viableTargets)
	{
		if (target == viableTarget)
		{
			return true;
		}
	}
	return false;
}

void AttackLongsword::OnSelected(Board* board, Unit* abilityUser)
{
	board->HalflightFields(Targetfinding::GetMeleeEnemyTargets(board, abilityUser, true));
}

void AttackLongsword::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
	board->HighlightField(hoveredField);
	if(CanUse(board, abilityUser, hoveredField))
	{
		abilityUser->ReduceTheoreticalEN(costEN);
		hoveredField->GetUnitOnField()->TakeTheoreticalDamage(damageNormal);
	}
}
