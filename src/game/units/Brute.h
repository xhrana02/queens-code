//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Unit.h"
#include "Movement.h"

class Brute : public Unit
{
public:
	Brute::Brute()
	{
		name = "Brute";
		this->maximumHP = 20;
		currentHP = maximumHP;
		currentEN = maximumEN;
		abilities.push_back(std::make_shared<Movement>());
		// warhammer
		// tackle
		// toughness
	}
};