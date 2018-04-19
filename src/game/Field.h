//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Unit.h"
#include <memory>

enum TerrainType {Empty, Border, Wall, IceBlock};

class Field
{
private:
	int positionX;
	int positionY;
	TerrainType terrainType;
	Unit* unitOnField = nullptr;
	std::shared_ptr<fsg::RenderingObject> fieldBorder = nullptr;
	std::shared_ptr<fsg::RenderingObject> fieldTerrain = nullptr;

public:
	Field(int position_x, int position_y) : Field(position_x, position_y, Empty) {}
	Field(int position_x, int position_y, TerrainType terrain_type)
		: positionX(position_x),
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

	void HighlightField() const;
	void UnhighlightField() const;

};
