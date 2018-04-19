//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Field.h"

using namespace fsg;
using namespace std;

vector<RenderingObject*> Field::GetRenderingObjects() const
{
	auto objects = vector<RenderingObject*>();
	if (fieldBorder)
	{
		objects.push_back(fieldBorder.get());
	}
	if (fieldTerrain)
	{
		objects.push_back(fieldTerrain.get());
	}
	if (GetUnitOnField() != nullptr)
	{
		objects.push_back(GetUnitOnField()->GetRenderingObject());
	}

	return objects;
}

void Field::MoveUnitToThisField(Unit* unit)
{
	if (IsFieldOccupied())
	{
		throw std::exception(
			"Field.MoveUnitToThisField: Invalid move, field is occupied.");
	}
	unitOnField = unit;
}

void Field::HighlightField() const
{
	if(fieldBorder)
	{
		fieldBorder->Highlight();
	}
}

void Field::UnhighlightField() const
{
	if(fieldBorder)
	{
		fieldBorder->Unhighlight();
	}
}
