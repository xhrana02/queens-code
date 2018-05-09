//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "SpecialHealingCircle.h"
#include "Game.h"
#include "Field.h"
#include "Flash.h"
#include "Targetfinding.h"

using namespace glm;

SpecialHealingCircle::SpecialHealingCircle()
{
    costEN = 8;
    name = "HealingCircle";
    iconPath = "icons/SpecialHealingCircle.png";
    description = "<b><u>HealingCircle</u> ( 8 EN )</b><br><br>"
        "Every allied unit in the range of 2 (excluding the priest) regains 4 HP and 4 EN.<br>";
	aiTargetValue = 40;
	aiTargetMissingHpMod = 0.6f;
	aiTargetMissingEnMod = 0.4f;
	aiTargetRelativeEnMod = 0.0f;
}

bool SpecialHealingCircle::Effect(Board* board, Unit* abilityUser, Field* target)
{
    if(CanUse(board, abilityUser, target))
    {
        abilityUser->ReduceEN(costEN);

        for (auto aoeTarget : viableTargets)
        {
            aoeTarget->GetUnitOnField()->Heal(healHP, healEN);

            if(game->IsRealGame())
            {
                // ReSharper disable once CppNonReclaimedResourceAcquisition
                new Flash(game, aoeTarget->GetUnitOnField(), vec4(0.0f, 1.0f, 0.0f, 0.5f), 3 + 1.5*healHP + healEN);
            }
        }
        PanCameraToTarget(abilityUser->GetOccupiedField());
        return true;
    }
    return false;
}

void SpecialHealingCircle::OnSelected(Board* board, Unit* abilityUser)
{
    board->HalflightFields(Targetfinding::GetIndirectAllyTargets(board, abilityUser, aoeRangeMin, aoeRangeMax, true));
}

void SpecialHealingCircle::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
    if(CanUse(board, abilityUser, hoveredField))
    {
        board->HighlightFields(viableTargets);
        abilityUser->ReduceTheoreticalEN(costEN);
        for (auto aoeTarget : viableTargets)
        {
            aoeTarget->GetUnitOnField()->TheoreticalHeal(healHP, healEN);
        }
    }
}

void SpecialHealingCircle::calculateViableTargets(Board* board, Unit* abilityUser)
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
