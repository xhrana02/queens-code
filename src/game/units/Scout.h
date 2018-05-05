//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Unit.h"
#include "MovementEnhanced.h"
#include "SpecialDirtyTrick.h"
#include "PassiveRunner.h"

class Scout : public Unit
{
public:
	Scout()
	{
		name = "Scout";
		this->maximumHP = 14;
		currentHP = maximumHP;
		currentEN = maximumEN;
		abilities.push_back(std::make_shared<MovementEnhanced>());
		abilities.push_back(std::make_shared<AttackShortSword>());
		abilities.push_back(std::make_shared<SpecialDirtyTrick>());
		abilities.push_back(std::make_shared<PassiveRunner>());
	}
};
