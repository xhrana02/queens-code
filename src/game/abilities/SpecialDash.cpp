//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
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
    costEN = 1;
    name = "Dash";
    iconPath = "icons/SpecialDash.png";
    description = "<b><u>Dash</u> ( 1 EN ) Indirect 1-3</b><br><br>"
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

bool SpecialDash::CanUse(Board* board, Unit* abilityUser, Field* target)
{
    if (target == nullptr)
    {
        return false;
    }

    auto viableTargets = Targetfinding::GetIndirectEmptyTargets(board, abilityUser->GetOccupiedField(), rangeMin, rangeMax);
    for (auto viableTarget : viableTargets)
    {
        if (target == viableTarget)
        {
            return true;
        }
    }
    return false;
}

void SpecialDash::OnSelected(Board* board, Unit* abilityUser)
{
    board->HalflightFields(Targetfinding::GetIndirectEmptyTargets(board, abilityUser->GetOccupiedField(), rangeMin, rangeMax));
}

void SpecialDash::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
    board->HighlightField(hoveredField);
    if(CanUse(board, abilityUser, hoveredField))
    {
        abilityUser->ReduceTheoreticalEN(costEN);
    }
}
