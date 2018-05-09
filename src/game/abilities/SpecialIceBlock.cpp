//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "SpecialIceBlock.h"
#include "Game.h"
#include "Field.h"
#include "Flash.h"
#include "Targetfinding.h"
#include "CommonTooltips.h"
#include "IceBlock.h"

using namespace glm;

SpecialIceBlock::SpecialIceBlock()
{
    costEN = 5;
    name = "Ice Block";
    iconPath = "icons/SpecialIceBlock.png";
    description = "<b><u>Ice Block</u> ( 5 EN ) Indirect 0-4</b><br><br>"
        "Freezes a tile until any damage is dealt to it. Units caught in the ice block "
        "are stunned but can't take any damage.<br>"
        STUN_TOOLTIP;
	aiTargetValue = 1;
}

bool SpecialIceBlock::Effect(Board* board, Unit* abilityUser, Field* target)
{
    if(CanUse(board, abilityUser, target))
    {
        abilityUser->ReduceEN(costEN);
        target->FreezeField();

        if(game->IsRealGame())
        {
            game->PanCameraToField(target);
            // ReSharper disable once CppNonReclaimedResourceAcquisition
            new Flash(game, target->GetUnitOnField(), vec4(0.0f, 0.0f, 1.0f, 0.0f), 20, 0);
        }
        return true;
    }
    return false;
}

void SpecialIceBlock::OnSelected(Board* board, Unit* abilityUser)
{
    board->HalflightFields(Targetfinding::GetIndirectAllTargets(board, abilityUser->GetOccupiedField(), rangeMin, rangeMax));
}

void SpecialIceBlock::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
    board->HighlightField(hoveredField);
    if(CanUse(board, abilityUser, hoveredField))
    {
        abilityUser->ReduceTheoreticalEN(costEN);
    }
}

void SpecialIceBlock::calculateViableTargets(Board* board, Unit* abilityUser)
{
	auto candidates = Targetfinding::GetIndirectAllTargets(board, abilityUser->GetOccupiedField(), rangeMin, rangeMax);
	viableTargets.clear();
	for (auto candidate : candidates)
	{
		if (!candidate->IsFieldFrozen())
		{
			viableTargets.push_back(candidate);
		}
	}
}
