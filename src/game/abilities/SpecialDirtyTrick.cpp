//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
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
    costEN = 4;
    name = "Dirty Trick";
    iconPath = "icons/SpecialDirtyTrick.png";
    description = "<b><u>Dirty Trick</u> ( 4 EN ) Melee</b><br><br>"
        "The target takes 3 EN damage and is stunned for 2 turns.<br>"
        STUN_TOOLTIP;
	aiTargetValue = 40;
}

bool SpecialDirtyTrick::Effect(Board* board, Unit* abilityUser, Field* target)
{
    if(CanUse(board, abilityUser, target))
    {
        abilityUser->ReduceEN(costEN);
        auto targetUnit = target->GetUnitOnField();
        targetUnit->Stun(stunDuration);
		targetUnit->TakeDamage(Melee, 0, 0, damageEN);

		if (!targetUnit->IsUnitAlive())
		{
			targetUnit->OnUnitDeath();
		}
		else if(game->IsRealGame())
        {
            // ReSharper disable once CppNonReclaimedResourceAcquisition
            new Flash(game, target->GetUnitOnField(), vec4(1.0f, 1.0f, 0.0f, 1.0f), 5 + 0.75*damageEN);
        }
		PanCameraToTarget(target);
        return true;
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

void SpecialDirtyTrick::calculateViableTargets(Board* board, Unit* abilityUser)
{
	auto candidates = Targetfinding::GetMeleeEnemyTargets(board, abilityUser);
	viableTargets.clear();
	for (auto candidate : candidates)
	{
		if (!candidate->IsFieldFrozen())
		{
			viableTargets.push_back(candidate);
		}
	}
}
