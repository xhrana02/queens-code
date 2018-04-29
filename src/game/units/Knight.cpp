//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
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

