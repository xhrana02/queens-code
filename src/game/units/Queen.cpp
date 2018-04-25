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
	this->maximumHitPoints = 10;
	currentHitPoints = maximumHitPoints;
	currentEnergy = maximumEnergy;
	abilities.push_back(new Movement());
}


