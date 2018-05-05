//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Unit.h"
#include "Movement.h"
#include "AttackLightningBolt.h"
#include "PassiveMeditation.h"
#include "SpecialIceBlock.h"

class Wizard : public Unit
{
public:
	Wizard()
	{
		name = "Wizard";
		this->maximumHP = 12;
		currentHP = maximumHP;
		currentEN = maximumEN;
		abilities.push_back(std::make_shared<Movement>());
		abilities.push_back(std::make_shared<AttackLightningBolt>());
		abilities.push_back(std::make_shared<SpecialIceBlock>());
		abilities.push_back(std::make_shared<PassiveMeditation>(this));
	}
};
