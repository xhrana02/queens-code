//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
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
