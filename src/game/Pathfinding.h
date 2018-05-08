//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include <set>
#include <vector>
#include <unordered_map>
#include <forward_list>
#include <unordered_set>

class Field;
class Board;

class Pathfinding
{
public:
    static std::forward_list<Field*> FindPath(Board* board, Field* origin, Field* target);
    static std::forward_list<Field*> ReconstructPath(std::unordered_map<Field*, Field*> cameFrom, Field* current);
    static float HeuristicCostEstimate(Field* origin, Field* target);

    static std::vector<Field*> GetAllPossibleTargets(Board* board, Field* origin, int maxLength);
    static std::vector<Field*> ConvertSetToVector(std::unordered_set<Field*> convertingSet);
};
