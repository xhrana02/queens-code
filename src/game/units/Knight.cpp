//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Knight.h"
#include <list>

Knight::Knight()
{
	this->maximumHitPoints = 20;
}

std::list<int>* Knight::GetListOfAbilites()
{
	return new std::list<int>();
}

