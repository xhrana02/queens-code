//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Targetfinding.h"
#include "Board.h"
#include "Field.h"
#include "Unit.h"

using namespace std;


vector<Field*> Targetfinding::GetMeleeEnemyTargets(Board* board, Unit* origin, bool includeEmpty)
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
            continue;
        }

        if (includeEmpty && !neighbor->IsFieldOccupied())
        {
            // Include empty tiles too if set
            targets.push_back(neighbor);
        }
    }

    return targets;
}

vector<Field*> Targetfinding::GetLineEnemyTargets(Board* board, Unit* origin, int rangeMin, int rangeMax, bool includeEmpty)
{
    auto targets = vector<Field*>();

    auto originX = origin->GetOccupiedField()->GetX();
    auto originY = origin->GetOccupiedField()->GetY();

    for (auto directionX = -1; directionX <=1; directionX++) {
    for (auto directionY = -1; directionY <=1; directionY++)
    {
        if (directionX == 0 && directionY == 0) {
            //skip no direction
            continue;
        }

        auto isDiagonal = (directionX != 0 && directionY != 0);
        auto diagonalTraveled = 0.0f;

        auto range = 0;
        auto posX = originX;
        auto posY = originY;

        while (true)
        {
            if (isDiagonal) {
                diagonalTraveled += 1.4142f;
                range = ceil(diagonalTraveled);
            } else {
                range++;
            }
            if (range > rangeMax) { break; } // Out of range

            posX += directionX;
            posY += directionY;
            auto field = board->GetField(posX, posY);

            // Is there an obstacle?
            if (field->IsFieldOccupied())
            {
                if (field->GetUnitOnField() == nullptr) {
                    // Dead end, blocked by terrain or border
                    break;
                }

                // Add enemies to the vector
                if (origin->IsEnemy(field->GetUnitOnField())) {
                    if (range < rangeMin) { break; } // Obstacle is too near
                    targets.push_back(field);
                    break;
                }
                // Continue if allied
                continue;
            }

            if (includeEmpty && range >= rangeMin)
            {
                // Include empty tiles too if set
                targets.push_back(field);
            }
        }
    }}

    return targets;
}


vector<Field*> Targetfinding::GetIndirectEnemyTargets(Board* board, Unit* origin, int rangeMin, int rangeMax, bool includeEmpty)
{
    auto targets = vector<Field*>();

    auto allFields = board->GetAllPlayFields();
    for (auto field : allFields)
    {
        if (!IsInRange(origin->GetOccupiedField(), field, rangeMin, rangeMax))
        {
            continue;
        }
        auto unit = field->GetUnitOnField();
        if (unit == nullptr)
        {
            if (includeEmpty)
            {
                // Include empty tiles too if set
                targets.push_back(field);
            }
            continue;
        }
        if (origin->IsEnemy(unit))
        {
            targets.push_back(field);
        }
    }

    return targets;
}

vector<Field*> Targetfinding::GetIndirectAllyTargets(Board* board, Unit* origin, int rangeMin, int rangeMax, bool includeEmpty)
{
    auto targets = vector<Field*>();

    auto allFields = board->GetAllPlayFields();
    for (auto field : allFields)
    {
        if (!IsInRange(origin->GetOccupiedField(), field, rangeMin, rangeMax))
        {
            continue;
        }
        auto unit = field->GetUnitOnField();
        if (unit == nullptr)
        {
            if (includeEmpty)
            {
                // Include empty tiles too if set
                targets.push_back(field);
            }
            continue;
        }
        if (!origin->IsEnemy(unit))
        {
            targets.push_back(field);
        }
    }

    return targets;
}

vector<Field*> Targetfinding::GetIndirectEmptyTargets(Board* board, Field* origin, int rangeMin, int rangeMax)
{
    auto targets = vector<Field*>();

    auto allFields = board->GetAllEmptyFields();
    for (auto field : allFields)
    {
        if (!IsInRange(origin, field, rangeMin, rangeMax))
        {
            continue;
        }
        targets.push_back(field);
    }

    return targets;
}

vector<Field*> Targetfinding::GetIndirectAllTargets(Board* board, Field* origin, int rangeMin, int rangeMax)
{
    auto targets = vector<Field*>();

    auto allFields = board->GetAllPlayFields();
    for (auto field : allFields)
    {
        if (!IsInRange(origin, field, rangeMin, rangeMax))
        {
            continue;
        }
        if (field->GetTerrainType() == Wall)
        {
            continue;
        }
        targets.push_back(field);
    }

    return targets;
}

bool Targetfinding::IsInRange(Field* origin, Field* target, int rangeMin, int rangeMax)
{
    auto deltaX = origin->GetX() - target->GetX();
    auto deltaY = origin->GetY() - target->GetY();
    auto range = sqrt(float(pow(deltaX, 2) + pow(deltaY, 2)));

    if (range < rangeMin - 0.0001 || range > rangeMax + 0.0001)
    {
        return false;
    }
    return true;
}
