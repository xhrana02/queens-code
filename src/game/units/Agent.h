//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Unit.h"
#include "Movement.h"
#include "AttackDagger.h"
#include "AttackShortbow.h"
#include "SpecialDash.h"

class Agent : public Unit
{
public:
	Agent()
	{
		name = "Agent";
		this->maximumHP = 12;
		currentHP = maximumHP;
		currentEN = maximumEN;
		abilities.push_back(std::make_shared<Movement>());
		abilities.push_back(std::make_shared<AttackDagger>());
		abilities.push_back(std::make_shared<AttackShortbow>());
		abilities.push_back(std::make_shared<SpecialDash>());
	}
};
