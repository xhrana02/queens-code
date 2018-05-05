//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
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