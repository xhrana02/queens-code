//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "SpecialDash.h"
#include "Game.h"
#include "Field.h"
#include "Flash.h"
#include "Targetfinding.h"

using namespace glm;

SpecialDash::SpecialDash()
{
    costEN = 3;
    name = "Dash";
    iconPath = "icons/SpecialDash.png";
    description = "<b><u>Dash</u> ( 3 EN ) Indirect 1-4</b><br><br>"
        "Jump to an empty tile.<br>";
}

bool SpecialDash::Effect(Board* board, Unit* abilityUser, Field* target)
{
    if(CanUse(board, abilityUser, target))
    {
        abilityUser->ReduceEN(costEN);
        target->MoveUnitToThisField(abilityUser);

        if(game->IsRealGame())
        {
            game->PanCameraToField(target);
            // ReSharper disable once CppNonReclaimedResourceAcquisition
            new Flash(game, abilityUser, vec4(0.0f, 0.0f, 0.0f, 0.0f), 10, 0);
        }
        return true;
    }
    return false;
}

void SpecialDash::OnSelected(Board* board, Unit* abilityUser)
{
	calculateViableTargets(board, abilityUser);
    board->HalflightFields(viableTargets);
}

void SpecialDash::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
    board->HighlightField(hoveredField);
    if(CanUse(board, abilityUser, hoveredField))
    {
        abilityUser->ReduceTheoreticalEN(costEN);
    }
}

void SpecialDash::calculateViableTargets(Board* board, Unit* abilityUser)
{
	viableTargets = Targetfinding::GetIndirectEmptyTargets(board, abilityUser->GetOccupiedField(), rangeMin, rangeMax);
}
