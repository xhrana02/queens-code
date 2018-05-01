//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Unit.h"
#include "Movement.h"

class Wizard : public Unit
{
public:
	Wizard::Wizard()
	{
		name = "Wizard";
		this->maximumHP = 12;
		currentHP = maximumHP;
		currentEN = maximumEN;
		abilities.push_back(std::make_shared<Movement>());
		// Lightning bolt
		// Ice block
		// Meditation
	}
};