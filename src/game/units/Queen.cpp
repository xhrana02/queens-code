//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Queen.h"
#include "Movement.h"

Queen::Queen()
{
	name = "Queen";
	this->maximumHP = 10;
	currentHP = maximumHP;
	currentEN = maximumEN;
	abilities.push_back(std::make_shared<Movement>());
}


