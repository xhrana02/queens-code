//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Pathfinding.h"
#include <set>

using namespace std;

vector<Field*> Pathfinding::FindPath(Board* board, Field* origin, Field* target)
{
	auto closedSet = set<Field*>();
	auto openSet = set<Field*>({ origin });
	auto cameFrom = unordered_map<Field*, Field*>();

	auto allEmptyFields = board->GetAllEmptyFields();

	auto gScore = unordered_map<Field*, int>();
	for (auto field : allEmptyFields)
	{
		gScore[field] = 9999;
	}
	gScore[origin] = 0;

	auto fScore = unordered_map<Field*, int>();
	for (auto field : allEmptyFields)
	{
		fScore[field] = 9999;
	}
	fScore[origin] = HeuristicCostEstimate(origin, target);

	while (!openSet.empty())
	{
		Field* current = nullptr;
		for (auto field : openSet)
		{
			if (current == nullptr)
			{
				current = field;
			}
			else
			{
				if (fScore[field] < fScore[current])
				{
					current = field;
				}
			}
		}

		if (current == target)
		{
			return ReconstructPath(cameFrom, current);
		}

		openSet.erase(current);
		closedSet.insert(current);

		for (auto neighbor : board->GetAllNeighborEmptyFields(current))
		{
			if (closedSet.count(neighbor) == 1)
			{
				// skip already evaluated fields
				continue;
			}

			if (openSet.count(neighbor) == 0)
			{
				openSet.insert(neighbor);
			}

			auto new_gScore = gScore[current] + 1;
			if (new_gScore >= gScore[neighbor])
			{
				// this is not a better path
				continue;
			}

			// record the new best path
			cameFrom[neighbor] = current;
			gScore[neighbor] = new_gScore;
			fScore[neighbor] = new_gScore + HeuristicCostEstimate(neighbor, target);
		}
	}

	return vector<Field*>();
}

vector<Field*> Pathfinding::ReconstructPath(unordered_map<Field*, Field*> cameFrom, Field* current)
{
	auto path = vector<Field*>({ current });
	while (cameFrom.count(current) == 1)
	{
		current = cameFrom[current];
		path.push_back(current);
	}
	return path;
}

int Pathfinding::HeuristicCostEstimate(Field* origin, Field* target)
{
	auto deltaX = abs(origin->GetX() - target->GetX());
	auto deltaY = abs(origin->GetY() - target->GetY());
	return deltaX + deltaY;
}
