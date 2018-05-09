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
    costEN = 6;
    name = "Blessing";
    iconPath = "icons/SpecialBlessing.png";
    description = "<b><u>Blessing</u> ( 6 EN )</b><br><br>"
        "Every allied unit in the range of 2 (including the priest) regains bonus 1 EN "
        "when regenerating and gains 1 Armor for the next 5 turns.<br>"
        ARMOR_TOOLTIP
        REGENERATION_TOOLTIP;
	aiTargetValue = 40;
	aiTargetMissingHpMod = 0.3f;
	aiTargetMissingEnMod = 0.2f;
	aiTargetRelativeEnMod = 0.5f;
}

bool SpecialBlessing::Effect(Board* board, Unit* abilityUser, Field* target)
{
    if(CanUse(board, abilityUser, target))
    {
        abilityUser->ReduceEN(costEN);

        for (auto aoeTarget : viableTargets)
        {
			auto targetUnit = aoeTarget->GetUnitOnField();
			targetUnit->ApplyBuff(new Blessing(targetUnit));

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

void SpecialBlessing::OnSelected(Board* board, Unit* abilityUser)
{
    board->HalflightFields(Targetfinding::GetIndirectAllyTargets(board, abilityUser, aoeRangeMin, aoeRangeMax, true));
}

void SpecialBlessing::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
    if(CanUse(board, abilityUser, hoveredField))
    {
        board->HighlightFields(viableTargets);
        abilityUser->ReduceTheoreticalEN(costEN);
    }
}

void SpecialBlessing::calculateViableTargets(Board* board, Unit* abilityUser)
{
	viableTargets.clear();
	for (auto field : Targetfinding::GetIndirectAllyTargets(board, abilityUser, aoeRangeMin, aoeRangeMax))
	{
		if (!field->IsFieldFrozen())
		{
			viableTargets.push_back(field);
		}
	}
}
