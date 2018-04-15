//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
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

