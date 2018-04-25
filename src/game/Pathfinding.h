//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Field.h"
#include "Board.h"

class Pathfinding
{
public:
	static std::vector<Field*> FindPath(Board* board, Field* origin, Field* target);
	static std::vector<Field*> ReconstructPath(std::unordered_map<Field*, Field*> cameFrom, Field* current);
	static int HeuristicCostEstimate(Field* origin, Field* target);
};
