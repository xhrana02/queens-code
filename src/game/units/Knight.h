//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Unit.h"
#include "Movement.h"
#include "AttackLongsword.h"
#include "AttackCrossbow.h"
#include "PassiveKnightsArmor.h"

class Knight : public Unit
{
public:
	Knight()
	{
		name = "Knight";
		this->maximumHP = 18;
		currentHP = maximumHP;
		currentEN = maximumEN;
		abilities.push_back(std::make_shared<Movement>());
		abilities.push_back(std::make_shared<AttackLongsword>());
		abilities.push_back(std::make_shared<AttackCrossbow>());
		abilities.push_back(std::make_shared<PassiveKnightsArmor>(this));
	}
};