//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Queen.h"
#include "Movement.h"
#include "PassiveThroneClaim.h"

Queen::Queen()
{
	name = "Queen";
	isRoyalty = true;
	this->maximumHP = 10;
	currentHP = maximumHP;
	currentEN = maximumEN;
	abilities.push_back(std::make_shared<Movement>());
	abilities.push_back(std::make_shared<PassiveThroneClaim>());
}


