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
		"Deals 9 normal damage to the target.<br><br>"
		NORMAL_DAMAGE_TOOLTIP;
}

bool AttackLongsword::Effect(Board* board, Unit* abilityUser, Field* target)
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
					// ReSharper disable once CppNonReclaimedResourceAcquisition
					new Flash(game, target->GetUnitOnField(), vec4(1.0f, 0.0f, 0.0f, 1.0f), normalDamage);
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

	auto viableTargets = calculateViableTargets(board, abilityUser);
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
	board->HalflightFields(calculateViableTargets(board, abilityUser));
}

std::vector<Field*> AttackLongsword::calculateViableTargets(Board* board, Unit* abilityUser)
{
	return Targetfinding::GetMeleeEnemyTargets(board, abilityUser);
}
