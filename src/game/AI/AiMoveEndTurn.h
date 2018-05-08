//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
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
