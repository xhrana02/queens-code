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
		throw exception("Field.MoveUnitToThisField: Invalid move, field is occupied.");
	}
	auto previousField = unit->GetOccupiedField();
	if(previousField != nullptr)
	{
		previousField->UnitLeavesThisField();
	}
	unitOnField = unit;
	unit->SetOccupiedField(this);
	unit->UpdateRenderingObjectPosition();

	fieldBorder->SetColors(
		unit->GetRenderingObject()->GetNormalColor(),
		unit->GetRenderingObject()->GetHalflightColor(),
		unit->GetRenderingObject()->GetHighlightColor()
	);
}

void Field::UnitLeavesThisField()
{
	unitOnField->SetOccupiedField(nullptr);
	unitOnField = nullptr;
	fieldBorder->SetColors(BORDER_NORMAL_COLOR, BORDER_HALFLIGHT_COLOR, BORDER_HIGHLIGHT_COLOR);
}

void Field::HighlightField() const
{
	if(fieldBorder)
	{
		fieldBorder->Highlight();
	}
	if(fieldTerrain)
	{
		fieldTerrain->Highlight();
	}
	if(unitOnField)
	{
		unitOnField->GetRenderingObject()->Highlight();
	}
}

void Field::UnhighlightField() const
{
	if(fieldBorder)
	{
		fieldBorder->Unhighlight();
	}
	if(fieldTerrain)
	{
		fieldTerrain->Unhighlight();
	}
	if(unitOnField)
	{
		unitOnField->GetRenderingObject()->Unhighlight();
	}
}

void Field::HalflightField() const
{
	if(fieldBorder)
	{
		fieldBorder->Halflight();
	}
	if(fieldTerrain)
	{
		fieldTerrain->Halflight();
	}
	if(unitOnField)
	{
		unitOnField->GetRenderingObject()->Halflight();
	}
}

void Field::UnhalflightField() const
{
	if(fieldBorder)
	{
		fieldBorder->Unhalflight();
	}
	if(fieldTerrain)
	{
		fieldTerrain->Unhalflight();
	}
	if(unitOnField)
	{
		unitOnField->GetRenderingObject()->Unhalflight();
	}
}

