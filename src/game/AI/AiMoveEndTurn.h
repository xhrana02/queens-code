//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "AiMove.h"

class Player;

class AiMoveEndTurn : public AiMove
{
public:
	PlayerID playerID;

	explicit AiMoveEndTurn(PlayerID inPlayerID);

	bool UseThisMove(Game* game) const override;
};
