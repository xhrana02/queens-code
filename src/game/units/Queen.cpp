//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
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


