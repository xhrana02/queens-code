//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "AttackSpear.h"
#include "Game.h"
#include "Field.h"
#include "Flash.h"
#include "Targetfinding.h"
#include "CommonTooltips.h"

using namespace glm;

AttackSpear::AttackSpear()
{
	costEN = 5;
	name = "Spear Attack";
	iconPath = "icons/AttackSpear.png";
	description = "<b><u>Spear Attack</u> ( 5 EN ) Line 1-2</b><br><br>"
		"Deals 3 HP and 5 normal damage to the target.<br>"
		HP_DAMAGE_TOOLTIP
		NORMAL_DAMAGE_TOOLTIP
		COMBINED_DAMAGE_TOOLTIP;
}

bool AttackSpear::Effect(Board* board, Unit* abilityUser, Field* target)
{
	if(CanUse(board, abilityUser, target))
	{
		abilityUser->ReduceEN(costEN);
		auto targetUnit = target->GetUnitOnField();
		targetUnit->TakeDamage(damageNormal, damageHP);

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
					new Flash(game, target->GetUnitOnField(), vec4(1.0f, 0.0f, 0.0f, 1.0f), 1.5*damageHP + damageNormal);
				}
			}
		}
		return true;
	}
	return false;
}

bool AttackSpear::CanUse(Board* board, Unit* abilityUser, Field* target)
{
	if (target == nullptr)
	{
		return false;
	}

	auto viableTargets = Targetfinding::GetLineEnemyTargets(board, abilityUser, 1, 2);
	for (auto viableTarget : viableTargets)
	{
		if (target == viableTarget)
		{
			return true;
		}
	}
	return false;
}

void AttackSpear::OnSelected(Board* board, Unit* abilityUser)
{
	board->HalflightFields(Targetfinding::GetLineEnemyTargets(board, abilityUser, 1, 2, true));
}

void AttackSpear::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
	board->HighlightField(hoveredField);
	if(CanUse(board, abilityUser, hoveredField))
	{
		abilityUser->ReduceTheoreticalEN(costEN);
		hoveredField->GetUnitOnField()->TakeTheoreticalDamage(damageNormal, damageHP);
	}
}
