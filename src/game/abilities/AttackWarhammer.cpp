//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "AttackWarhammer.h"
#include "Game.h"
#include "Field.h"
#include "Flash.h"
#include "Targetfinding.h"
#include "CommonTooltips.h"

using namespace glm;

AttackWarhammer::AttackWarhammer()
{
	costEN = 7;
	name = "Warhammer Attack";
	iconPath = "icons/AttackWarhammer.png";
	description = "<b><u>Warhammer Attack</u> ( 7 EN ) Melee</b><br><br>"
		"Deals 5 HP and 5 normal damage to the target.<br>"
		HP_DAMAGE_TOOLTIP
		NORMAL_DAMAGE_TOOLTIP
		COMBINED_DAMAGE_TOOLTIP;
}

bool AttackWarhammer::Effect(Board* board, Unit* abilityUser, Field* target)
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

bool AttackWarhammer::CanUse(Board* board, Unit* abilityUser, Field* target)
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

void AttackWarhammer::OnSelected(Board* board, Unit* abilityUser)
{
	board->HalflightFields(Targetfinding::GetMeleeEnemyTargets(board, abilityUser, true));
}

void AttackWarhammer::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
	board->HighlightField(hoveredField);
	if(CanUse(board, abilityUser, hoveredField))
	{
		abilityUser->ReduceTheoreticalEN(costEN);
		hoveredField->GetUnitOnField()->TakeTheoreticalDamage(damageNormal, damageHP);
	}
}
