//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Ability.h"
#include "Unit.h"
#include "Board.h"
#include "Game.h"

bool Ability::CanAfford(Unit* abilityUser) const
{
    if (abilityUser->GetCurrentEnergy() < costEN)
    {
        return false;
    }
    if (abilityUser->GetCurrentHitPoints() <= costHP)
    {
        // <= instead of < so a unit can't kill itself
        return false;
    }
    return true;
}

void Ability::CalculateViableTargets(Board* board, Unit* abilityUser)
{
	if (abilityUser->IsStunned())
	{
		viableTargets = std::vector<Field*>();
	}
	else
	{
		calculateViableTargets(board, abilityUser);
	}
}

void Ability::PanCameraToTarget(Field* target) const
{
    if(game->IsRealGame())
    {
        game->PanCameraToField(target);
    }
}

bool Ability::CanUse(Board* board, Unit* abilityUser, Field* target)
{
	if (target == nullptr)
	{
		return false;
	}

	calculateViableTargets(board, abilityUser);

	for (auto viableTarget : viableTargets)
	{
		if (target == viableTarget)
		{
			return true;
		}
	}
	return false;
}

void Ability::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
    board->HighlightField(hoveredField);
}
