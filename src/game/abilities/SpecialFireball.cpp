//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "SpecialFireball.h"
#include "Game.h"
#include "Field.h"
#include "Flash.h"
#include "Targetfinding.h"
#include "CommonTooltips.h"

using namespace glm;

SpecialFireball::SpecialFireball()
{
    costEN = 6;
    name = "Fireball";
    iconPath = "icons/SpecialFireball.png";
    description = "<b><u>Fireball</u> ( 6 EN ) Line 1-6</b><br><br>"
        "Deals 6 normal damage to the target. Deals 4 normal damage to tiles in range of 2 around the target. Can target empty tiles.<br>"
        NORMAL_DAMAGE_TOOLTIP;
	aiTargetValue = 1;
	aiCanHurt = true;
	aiTargetMissingHpMod = 0.5f;
	aiTargetMissingEnMod = 1.0f;
	aiTargetRelativeEnMod = 0.0f;
}

bool SpecialFireball::Effect(Board* board, Unit* abilityUser, Field* target)
{
    if(CanUse(board, abilityUser, target))
    {
        abilityUser->ReduceEN(costEN);
        abilityUser->ReduceHP(costHP);

        CalculateAreaOfEffect(board, target);
        for (auto aoeTarget : areaOfEffectTargets)
        {
            auto damage = 0;
            if (aoeTarget == target) {
                damage = damageNormal0;
            } else {
                damage = damageNormal2;
            }

            auto targetUnit = aoeTarget->GetUnitOnField();
            targetUnit->TakeDamage(Line, damage);

            if (!targetUnit->IsUnitAlive())
            {
                targetUnit->OnUnitDeath();
            }
            else
            {
                if(game->IsRealGame())
                {
                    // ReSharper disable once CppNonReclaimedResourceAcquisition
                    new Flash(game, targetUnit, vec4(1.0f, 0.7f, 0.3f, 1.0f), 3 + damage);
                }
            }
        }
        PanCameraToTarget(target);
        return true;
    }
    return false;
}

void SpecialFireball::OnSelected(Board* board, Unit* abilityUser)
{
	calculateViableTargets(board, abilityUser);
    board->HalflightFields(viableTargets);
}

void SpecialFireball::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
    CalculateAreaOfEffect(board, hoveredField);
    board->HighlightFields(areaOfEffectCandidates);
    if(CanUse(board, abilityUser, hoveredField))
    {
        abilityUser->ReduceTheoreticalEN(costEN);
        abilityUser->ReduceTheoreticalHP(costHP);
        for (auto aoeTarget : areaOfEffectTargets)
        {
            if (aoeTarget == hoveredField) {
                aoeTarget->GetUnitOnField()->TakeTheoreticalDamage(Line, damageNormal0);
            } else {
                aoeTarget->GetUnitOnField()->TakeTheoreticalDamage(Line, damageNormal2);
            }
        }
    }
}

void SpecialFireball::calculateViableTargets(Board* board, Unit* abilityUser)
{
	viableTargets = Targetfinding::GetLineEnemyTargets(board, abilityUser, rangeMin, rangeMax, true);
}

void SpecialFireball::CalculateAreaOfEffect(Board* board, Field* center)
{
    areaOfEffectCandidates.clear();
    areaOfEffectCandidates = Targetfinding::GetIndirectAllTargets(board, center, aoeRangeMin, aoeRangeMax);
    areaOfEffectTargets.clear();
    for (auto field : areaOfEffectCandidates)
    {
        if (field->GetUnitOnField())
        {
            areaOfEffectTargets.push_back(field);
        }
    }
}
