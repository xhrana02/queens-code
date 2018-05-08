//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
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
