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
	name = "Queen";
	this->maximumHP = 10;
	currentHP = maximumHP;
	currentEN = maximumEN;
	abilities.push_back(std::make_shared<Movement>());
}


