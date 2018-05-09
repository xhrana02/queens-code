//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Pathfinding.h"
#include "Board.h"
#include "Field.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

forward_list<Field*> Pathfinding::FindPath(Board* board, Field* origin, Field* target)
{
    auto closedSet = unordered_set<Field*>();
    auto openSet = unordered_set<Field*>({ origin });
    auto cameFrom = unordered_map<Field*, Field*>();

    auto allEmptyFields = board->GetAllEmptyFields();

    auto gScore = unordered_map<Field*, int>();
    for (auto field : allEmptyFields)
    {
        gScore[field] = 9999;
    }
    gScore[origin] = 0;

    auto fScore = unordered_map<Field*, double>();
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

        for (auto neighbor : board->GetAllMovementNeighborFields(current))
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
                if (new_gScore > gScore[neighbor] || fScore[current] > fScore[cameFrom[neighbor]])
                {
                    // this is not a better path
                    continue;
                }
            }

            // record the new best path
            cameFrom[neighbor] = current;
            gScore[neighbor] = new_gScore;
            fScore[neighbor] = new_gScore + HeuristicCostEstimate(neighbor, target);
        }
    }

    return forward_list<Field*>();
}

forward_list<Field*> Pathfinding::ReconstructPath(unordered_map<Field*, Field*> cameFrom, Field* current)
{
    auto path = forward_list<Field*>({ current });
    while (cameFrom.count(current) == 1)
    {
        current = cameFrom[current];
        path.push_front(current);
    }
    return path;
}

float Pathfinding::HeuristicCostEstimate(Field* origin, Field* target)
{
    auto deltaX = abs(origin->GetX() - target->GetX());
    auto deltaY = abs(origin->GetY() - target->GetY());
	return 0.8f * sqrt(float(pow(deltaX, 2) + pow(deltaY, 2)));
}


vector<Field*> Pathfinding::GetAllPossibleTargets(Board* board, Field* origin, int maxLength)
{
    auto closedSet = unordered_set<Field*>();
    auto openSet = unordered_set<Field*>({ origin });

    auto allEmptyFields = board->GetAllEmptyFields();

    for (auto field : allEmptyFields)
    {
        field->CostToGetHere = 9999;
    }
    origin->CostToGetHere = 0;

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
                if (field->CostToGetHere < current->CostToGetHere)
                {
                    current = field;
                }
            }
        }

        if (current->CostToGetHere > maxLength)
        {
            // If all viable targets were searched, convert closedSet to vector and return it
            // Origin field isn't a valid target so it has to be removed first
            closedSet.erase(origin);
            return ConvertSetToVector(closedSet);
        }

        openSet.erase(current);
        closedSet.insert(current);

        for (auto neighbor : board->GetAllMovementNeighborFields(current))
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

            auto new_gScore = current->CostToGetHere + 1;
            if (new_gScore >= neighbor->CostToGetHere)
            {
                // this is not a better path
                continue;
            }

            // record the new best path
			neighbor->CostToGetHere = new_gScore;
        }
    }

    // If we ran out of fields to search trough, return all of the searched fields
    // Origin field isn't a valid target so it has to be removed first
    closedSet.erase(origin);
    return ConvertSetToVector(closedSet);
}

vector<Field*> Pathfinding::ConvertSetToVector(unordered_set<Field*> convertingSet)
{
    auto returnVector = vector<Field*>();
    for (auto field : convertingSet)
    {
        returnVector.push_back(field);
    }
    return returnVector;
}
