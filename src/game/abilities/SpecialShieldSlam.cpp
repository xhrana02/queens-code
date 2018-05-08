//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "SpecialShieldSlam.h"
#include "Game.h"
#include "Field.h"
#include "Flash.h"
#include "Targetfinding.h"
#include "CommonTooltips.h"

using namespace glm;

SpecialShieldSlam::SpecialShieldSlam()
{
    costEN = 2;
    name = "Shield Slam";
    iconPath = "icons/SpecialShieldSlam.png";
    description = "<b><u>Shield Slam</u> ( 2 EN ) Melee</b><br><br>"
        "The target takes 5 EN damage and is stunned for 1 turn.<br>"
        STUN_TOOLTIP
        EN_DAMAGE_TOOLTIP;
	aiTargetValue = 15;
}

bool SpecialShieldSlam::Effect(Board* board, Unit* abilityUser, Field* target)
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
        else
        {
            if(game->IsRealGame())
            {
                // ReSharper disable once CppNonReclaimedResourceAcquisition
                new Flash(game, target->GetUnitOnField(), vec4(1.0f, 1.0f, 0.0f, 1.0f), 5 + 0.75 * damageEN);
            }
        }
        PanCameraToTarget(target);
        return true;
    }
    return false;
}

void SpecialShieldSlam::OnSelected(Board* board, Unit* abilityUser)
{
    board->HalflightFields(Targetfinding::GetMeleeEnemyTargets(board, abilityUser, true));
}

void SpecialShieldSlam::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
    board->HighlightField(hoveredField);
    if(CanUse(board, abilityUser, hoveredField))
    {
        abilityUser->ReduceTheoreticalEN(costEN);
        hoveredField->GetUnitOnField()->TakeTheoreticalDamage(Melee, 0, 0, damageEN);
    }
}

void SpecialShieldSlam::calculateViableTargets(Board* board, Unit* abilityUser)
{
	viableTargets = Targetfinding::GetMeleeEnemyTargets(board, abilityUser);
}
