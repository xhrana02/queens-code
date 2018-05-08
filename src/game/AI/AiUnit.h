//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Unit.h"

class AiUnit : public Unit
{
	bool aiHasDash = false;
public:
	explicit AiUnit(Unit* source);

	std::vector<std::shared_ptr<AiMove>> GetAllPossibleMoves() override;
	bool CanUnitMove() const override;
	float GetMissingHP() override;
	float GetMissingEN() override;
	float GetRelativeEN() override;
};
