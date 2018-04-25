//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Unit.h"
#include "RenderingObject.h"
#include <memory>
#include <vector>

#define BORDER_NORMAL_COLOR glm::vec4(0.94f, 0.89f, 0.66f, 1.0f)
#define BORDER_HIGHLIGHT_COLOR glm::vec4(0.97f, 0.94f, 0.83f, 0.5f)

class Board;

enum TerrainType {Empty, Border, Wall, IceBlock};

class Field
{
private:
	Board* board = nullptr;
	int positionX;
	int positionY;
	TerrainType terrainType;
	Unit* unitOnField = nullptr;
	std::shared_ptr<fsg::RenderingObject> fieldBorder = nullptr;
	std::shared_ptr<fsg::RenderingObject> fieldTerrain = nullptr;

public:
	Field(Board* inBoard, int position_x, int position_y, TerrainType terrain_type = Empty)
		: board(inBoard),
	      positionX(position_x),
		  positionY(position_y),
		  terrainType(terrain_type)
	{
	}

	std::vector<fsg::RenderingObject*> GetRenderingObjects() const;

	void SetFieldBorderObject(std::shared_ptr<fsg::RenderingObject> newObject)
	{
		fieldBorder = newObject;
	}
	void SetFieldTerrainObject(std::shared_ptr<fsg::RenderingObject> newObject)
	{
		fieldTerrain = newObject;
	}

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

	TerrainType GetTerrainType() const
	{
		return terrainType;
	}

	void SetTerrainType(TerrainType type)
	{
		terrainType = type;
	}

	Unit* GetUnitOnField() const
	{
		return unitOnField;
	}

	bool IsFieldOccupied() const
	{
		return (GetTerrainType() != Empty || GetUnitOnField() != nullptr);
	}

	void MoveUnitToThisField(Unit* unit);
	void UnitLeavesThisField();

	void HighlightField() const;
	void UnhighlightField() const;

};
