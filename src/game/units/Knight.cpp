//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Knight.h"

Knight::Knight()
{
	this->maximumHitPoints = 20;
}

std::vector<Ability>* Knight::GetListOfAbilites()
{
	return new std::vector<Ability>();
}

