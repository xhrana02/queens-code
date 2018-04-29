//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Targetfinding.h"
#include "Board.h"
#include "Field.h"
#include "Unit.h"

using namespace std;



::vector<Field*> Targetfinding::GetMeleeEnemyTargets(Board* board, Unit* origin)
{
	auto targets = vector<Field*>();

	for (auto neighbor : board->GetAllMeleeNeighborFields(origin->GetOccupiedField()))
	{
		auto neighborUnit = neighbor->GetUnitOnField();
		if (neighborUnit != nullptr)
		{
			if (origin->IsEnemy(neighborUnit))
			{
				targets.push_back(neighbor);
			}
		}
	}

	return targets;
}

vector<Field*> Targetfinding::GetLineEnemyTargets(Board* board, Unit* origin, int rangeMin, int rangeMax)
{
	return vector<Field*>();
}

vector<Field*> Targetfinding::GetLineAllTargets(Board* board, Unit* origin, int rangeMin, int rangeMax)
{
	return vector<Field*>();
}

bool Targetfinding::IsClearShot(Board* board, Unit* origin, Field* target)
{
	return false;
}

vector<Field*> Targetfinding::GetIndirectEnemyTargets(Board* board, Unit* origin, int rangeMin, int rangeMax)
{
	return vector<Field*>();
}

vector<Field*> Targetfinding::GetIndirectAllyTargets(Board* board, Unit* origin, int rangeMin, int rangeMax)
{
	return vector<Field*>();
}

vector<Field*> Targetfinding::GetIndirectEmptyTargets(Board* board, Unit* origin, int rangeMin, int rangeMax)
{
	return vector<Field*>();
}

vector<Field*> Targetfinding::GetIndirectAllTargets(Board* board, Unit* origin, int rangeMin, int rangeMax)
{
	return vector<Field*>();
}

int Targetfinding::GetRange(Board* board, Field* origin, Field* target)
{
	return 0;
}
