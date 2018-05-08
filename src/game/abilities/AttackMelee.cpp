//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "AttackMelee.h"
#include "Game.h"
#include "Field.h"
#include "Flash.h"
#include "Targetfinding.h"

using namespace glm;

bool AttackMelee::Effect(Board* board, Unit* abilityUser, Field* target)
{
    if(CanUse(board, abilityUser, target))
    {
        abilityUser->ReduceEN(costEN);
        auto targetUnit = target->GetUnitOnField();
        targetUnit->TakeDamage(Melee, damageNormal, damageHP, damageEN);

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

void AttackMelee::OnSelected(Board* board, Unit* abilityUser)
{
    board->HalflightFields(Targetfinding::GetMeleeEnemyTargets(board, abilityUser, true));
}

void AttackMelee::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
    board->HighlightField(hoveredField);
    if(CanUse(board, abilityUser, hoveredField))
    {
        abilityUser->ReduceTheoreticalEN(costEN);
        hoveredField->GetUnitOnField()->TakeTheoreticalDamage(Melee, damageNormal, damageHP, damageEN);
    }
}

void AttackMelee::calculateViableTargets(Board* board, Unit* abilityUser)
{
	viableTargets = Targetfinding::GetMeleeEnemyTargets(board, abilityUser);
}
