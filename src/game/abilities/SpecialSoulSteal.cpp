//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "SpecialSoulSteal.h"
#include "Game.h"
#include "Field.h"
#include "Flash.h"
#include "Targetfinding.h"
#include "CommonTooltips.h"

using namespace glm;

SpecialSoulSteal::SpecialSoulSteal()
{
    costHP = 1;
	costEN = 3;
    name = "Soul Steal";
    iconPath = "icons/SpecialSoulSteal.png";
    description = "<b><u>Soul Steal</u> ( 1 HP, 3 EN ) Melee</b><br><br>"
        "Deals 6 HP damage to the target. Regains HP equal to the damage dealt.<br>"
        HP_DAMAGE_TOOLTIP;
	aiTargetValue = 20;
	aiCanHurt = true;
	aiTargetMissingHpMod = 0.3f;
	aiTargetMissingEnMod = 0.0f;
	aiTargetRelativeEnMod = 0.0f;
}

bool SpecialSoulSteal::Effect(Board* board, Unit* abilityUser, Field* target)
{
    if(CanUse(board, abilityUser, target))
    {
        abilityUser->ReduceEN(costEN);
        abilityUser->ReduceHP(costHP);
        auto targetUnit = target->GetUnitOnField();
        auto damageDealt = targetUnit->TakeDamage(Melee, 0, damageHP);
        abilityUser->Heal(damageDealt);

        if (!targetUnit->IsUnitAlive())
        {
            targetUnit->OnUnitDeath();
        }
        else
        {
            if(game->IsRealGame())
            {
                // ReSharper disable once CppNonReclaimedResourceAcquisition
                new Flash(game, abilityUser, vec4(0.0f, 1.0f, 0.0f, 1.0f), 3 + 1.5*damageHP);
                // ReSharper disable once CppNonReclaimedResourceAcquisition
                new Flash(game, targetUnit, vec4(0.5f, 0.0f, 0.0f, 0.5f), 1.5*damageHP, 0);
            }
        }
        PanCameraToTarget(target);
        return true;
    }
    return false;
}

void SpecialSoulSteal::OnSelected(Board* board, Unit* abilityUser)
{
    board->HalflightFields(Targetfinding::GetMeleeEnemyTargets(board, abilityUser, true));
}

void SpecialSoulSteal::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
    board->HighlightField(hoveredField);
    if(CanUse(board, abilityUser, hoveredField))
    {
        abilityUser->ReduceTheoreticalEN(costEN);
        abilityUser->ReduceTheoreticalHP(costHP);
        auto damageDealt = hoveredField->GetUnitOnField()->TakeTheoreticalDamage(Melee, 0, damageHP);
        abilityUser->TheoreticalHeal(damageDealt);
    }
}

void SpecialSoulSteal::calculateViableTargets(Board* board, Unit* abilityUser)
{
	viableTargets = Targetfinding::GetMeleeEnemyTargets(board, abilityUser);
}
