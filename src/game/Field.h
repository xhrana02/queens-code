//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "GameEnums.h"
#include "Unit.h"
#include "RenderingObject.h"
#include <memory>
#include <vector>

#define BORDER_NORMAL_COLOR glm::vec4(0.93f, 0.88f, 0.36f, 0.9f)
#define BORDER_HALFLIGHT_COLOR glm::vec4(0.40f, 0.95f, 0.30f, 0.9f)
#define BORDER_HIGHLIGHT_COLOR glm::vec4(0.98f, 0.97f, 0.90f, 0.9f)

#define ICE_BLOCK_NORMAL_COLOR glm::vec4(0.88f,0.88f,0.88f, 0.7f)
#define ICE_BLOCK_HALFLIGHT_COLOR glm::vec4(1.0f, 0.3f, 0.3f, 0.7f)
#define ICE_BLOCK_HIGHLIGHT_COLOR glm::vec4(1.0f, 1.0f, 1.0f, 0.3f)

class IceBlock;
class Board;

class Field
{
    Board* board = nullptr;
    int positionX;
    int positionY;
    TerrainType terrainType;
    std::shared_ptr<fsg::RenderingObject> fieldBorder = nullptr;
    std::shared_ptr<fsg::RenderingObject> fieldTerrain = nullptr;
    std::shared_ptr<fsg::RenderingObject> fieldIceBlock = nullptr;
    std::shared_ptr<IceBlock> iceBlockUnit = nullptr;
    bool frozen = false;
    Unit* unitOnField = nullptr;

public:
    Field(Board* inBoard, int position_x, int position_y, TerrainType terrain_type = Empty)
        : board(inBoard),
          positionX(position_x),
          positionY(position_y),
          terrainType(terrain_type)
    {
    }

    std::vector<fsg::RenderingObject*> GetRenderingObjects() const;

    void SetFieldBorderObject(std::shared_ptr<fsg::RenderingObject> newBorder)
    {
        fieldBorder = newBorder;
    }
    void SetFieldTerrainObject(std::shared_ptr<fsg::RenderingObject> newTerrain)
    {
        fieldTerrain = newTerrain;
    }
    void SetFieldIceBlockObject(std::shared_ptr<fsg::RenderingObject> newIceBlock);
    void SetFieldIceBlockUnit(std::shared_ptr<IceBlock> newIceBlock);

    Board* GetBoard() const
    {
        return board;
    }

    int GetX() const
    {
        return positionX;
    }

    int GetY() const
    {
        return positionY;
    }

    float GetRenderingPosX() const;
    float GetRenderingPosZ() const;

    TerrainType GetTerrainType() const
    {
        return terrainType;
    }

    void SetTerrainType(TerrainType type)
    {
        terrainType = type;
    }

    Unit* GetUnitOnField() const;
    bool IsFieldOccupied() const;
    bool IsFieldFrozen() const;

    void MoveUnitToThisField(Unit* unit);
    void UnitLeavesThisField();
    void FreezeField();
    void IceBlockDestroyed();

    void HighlightField() const;
    void UnhighlightField() const;
    void HalflightField() const;
    void UnhalflightField() const;

};
