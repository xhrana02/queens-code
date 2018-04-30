//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include <vector>
#include "Field.h"

class Unit;
class Board;

class Targetfinding
{
public:
	static std::vector<Field*> GetMeleeEnemyTargets(Board* board, Unit* origin, bool includeEmpty = false);

	static std::vector<Field*> GetLineEnemyTargets(Board* board, Unit* origin, int rangeMin, int rangeMax, bool includeEmpty = false);

	static std::vector<Field*> GetIndirectEnemyTargets(Board* board, Unit* origin, int rangeMin, int rangeMax, bool includeEmpty = false);
	static std::vector<Field*> GetIndirectAllyTargets(Board* board, Unit* origin, int rangeMin, int rangeMax, bool includeEmpty = false);
	static std::vector<Field*> GetIndirectEmptyTargets(Board* board, Unit* origin, int rangeMin, int rangeMax);
	static std::vector<Field*> GetIndirectAllTargets(Board* board, Unit* origin, int rangeMin, int rangeMax);
	static bool IsInRange(Field* origin, Field* target, int rangeMin, int rangeMax);
};
