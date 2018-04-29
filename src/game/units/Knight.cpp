//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Knight.h"
#include "Movement.h"
#include "AttackLongsword.h"
#include "PassiveKnightsArmor.h"

Knight::Knight()
{
	name = "Knight";
	this->maximumHP = 18;
	currentHP = maximumHP;
	currentEN = maximumEN;
	damageReduction = 2;
	abilities.push_back(std::make_shared<Movement>());
	abilities.push_back(std::make_shared<AttackLongsword>());
	abilities.push_back(std::make_shared<PassiveKnightsArmor>());
}

