//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "GameEnums.h"

class Game;
class Field;
class Unit;

class AiMove
{
public:
	AiMoveType type = AbilityUseMove;
	int userX = 0;
	int userY = 0;
	int targetX = 0;
	int targetY = 0;
	int abilitySlot = 0;
	int costToGetHere = 0;

	virtual ~AiMove() = default;
	AiMove(){}
	explicit AiMove(Unit* inAbilityUser, Field* inTarget, int inAbilitySlot);

	virtual bool UseThisMove(Game* game) const;
};
