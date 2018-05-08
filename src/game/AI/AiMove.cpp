//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "AiMove.h"
#include "Game.h"
#include "Board.h"
#include "Field.h"
#include "Unit.h"
#include <QDebug>

AiMove::AiMove(Unit* inAbilityUser, Field* inTarget, int inAbilitySlot)
{
	userX = inAbilityUser->GetOccupiedField()->GetX();
	userY = inAbilityUser->GetOccupiedField()->GetY();
	targetX = inTarget->GetX();
	targetY = inTarget->GetY();
	abilitySlot = inAbilitySlot;
}

bool AiMove::UseThisMove(Game* game) const
{
	auto board = game->GetGameBoard();
	auto user = board->GetField(userX, userY)->GetUnitOnField();
	auto target = board->GetField(targetX, targetY);

	if (user->UseAbilityBySlot(target, abilitySlot))
	{
		return true;
	}

	qDebug() << "AiMove::UseThisMove - " << user->GetName() << " on X:" << userX << " Y:" << userY
		<< " tried to use " << user->GetAbilityBySlot(abilitySlot)->GetName() << " on X:" << targetX
		<< " Y:" << targetY << " but failed.";
	return false;
}
