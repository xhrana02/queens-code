//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Ability.h"
#include "Unit.h"
#include "Board.h"

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

void Ability::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
	board->HighlightField(hoveredField);
}
