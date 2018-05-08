//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "AiMoveEndTurn.h"
#include "Game.h"
#include "Player.h"


AiMoveEndTurn::AiMoveEndTurn(PlayerID inPlayerID)
{
	playerID = inPlayerID;
	type = EndTurnMove;
}

bool AiMoveEndTurn::UseThisMove(Game* game) const
{
	game->GetPlayerByID(playerID)->EndTurn();
	return true;
}
