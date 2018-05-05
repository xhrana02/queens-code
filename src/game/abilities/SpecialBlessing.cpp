//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "SpecialBlessing.h"
#include "Game.h"
#include "Field.h"
#include "Flash.h"
#include "Targetfinding.h"
#include "CommonTooltips.h"
#include "Blessing.h"

using namespace glm;

SpecialBlessing::SpecialBlessing()
{
    costEN = 5;
    name = "Blessing";
    iconPath = "icons/SpecialBlessing.png";
    description = "<b><u>Blessing</u> ( 5 EN ) Indirect 0-2</b><br><br>"
        "Every allied unit in the range of 2 (including the priest) regains bonus 1 EN "
        "when regenerating and gains 1 Armor for the next 3 turns.<br>"
        ARMOR_TOOLTIP
        REGENERATION_TOOLTIP;
}

bool SpecialBlessing::Effect(Board* board, Unit* abilityUser, Field* target)
{
    if(CanUse(board, abilityUser, target))
    {
        abilityUser->ReduceEN(costEN);

        for (auto aoeTarget : areaOfEffectTargets)
        {
            aoeTarget->GetUnitOnField()->ApplyBuff(new Blessing());

            if(game->IsRealGame())
            {
                // ReSharper disable once CppNonReclaimedResourceAcquisition
                new Flash(game, aoeTarget->GetUnitOnField(), vec4(1.0f, 1.0f, 0.5f, 0.5f), 20, 15);
            }
        }
        PanCameraToTarget(abilityUser->GetOccupiedField());
        return true;
    }
    return false;
}

bool SpecialBlessing::CanUse(Board* board, Unit* abilityUser, Field* target)
{
    if (target == nullptr)
    {
        return false;
    }

    CalculateAreaOfEffect(board, abilityUser);
    for (auto viableTarget : areaOfEffectTargets)
    {
        if (target == viableTarget)
        {
            return true;
        }
    }
    return false;
}

void SpecialBlessing::OnSelected(Board* board, Unit* abilityUser)
{
    CalculateAreaOfEffect(board, abilityUser);
    board->HalflightFields(areaOfEffectCandidates);
}

void SpecialBlessing::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
    if(CanUse(board, abilityUser, hoveredField))
    {
        board->HighlightFields(areaOfEffectTargets);
        abilityUser->ReduceTheoreticalEN(costEN);
    }
}

void SpecialBlessing::CalculateAreaOfEffect(Board* board, Unit* abilityUser)
{
    areaOfEffectCandidates.clear();
    areaOfEffectCandidates = Targetfinding::GetIndirectAllyTargets(board, abilityUser, aoeRangeMin, aoeRangeMax);
    areaOfEffectTargets.clear();
    for (auto field : areaOfEffectCandidates)
    {
        if (field->GetUnitOnField() && !field->IsFieldFrozen())
        {
            areaOfEffectTargets.push_back(field);
        }
    }
}
