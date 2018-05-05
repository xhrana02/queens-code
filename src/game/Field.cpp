//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Field.h"
#include "Board.h"
#include "IceBlock.h"

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
    if (unitOnField)
    {
        objects.push_back(unitOnField->GetRenderingObject());
    }
    if (fieldIceBlock)
    {
        objects.push_back(iceBlockUnit->GetRenderingObject());
    }

    return objects;
}

void Field::SetFieldIceBlockObject(std::shared_ptr<fsg::RenderingObject> newIceBlock)
{
    fieldIceBlock = newIceBlock;
    fieldIceBlock->SetInvisible();
}

void Field::SetFieldIceBlockUnit(std::shared_ptr<IceBlock> newIceBlock)
{
    iceBlockUnit = newIceBlock;
    iceBlockUnit->SetOccupiedField(this);
    iceBlockUnit->SetIceBlockObject(fieldIceBlock.get());
}


/**
* \brief Rendering position X.
*/
float Field::GetRenderingPosX() const
{
    return positionX - (board->PlayableWidth() + 1) / 2.0f;
}

/**
* \brief Rendering position Z (Z in rendering coords, Y in game coords).
*/
float Field::GetRenderingPosZ() const
{
    return positionY - (board->PlayableHeight() + 1) / 2.0f;
}

Unit* Field::GetUnitOnField() const
{
    if (IsFieldFrozen())
    {
        return iceBlockUnit.get();
    }
    return unitOnField;
}

bool Field::IsFieldOccupied() const
{
    if (GetTerrainType() != Empty && GetTerrainType() != Throne)
    {
        return true;
    }
    if (GetUnitOnField() != nullptr)
    {
        return true;
    }
    if (IsFieldFrozen())
    {
        return true;
    }
    return false;
}

bool Field::IsFieldFrozen() const
{
    return frozen;
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

void Field::FreezeField()
{
    frozen = true;
    fieldIceBlock->SetVisible();
    if (unitOnField != nullptr)
    {
        unitOnField->Stun(1);
    }
}

void Field::IceBlockDestroyed()
{
    frozen = false;
    fieldIceBlock->SetInvisible();
    if (unitOnField)
    {
        unitOnField->OnFreezeEnd();
    }
}

void Field::HighlightField() const
{
    if (fieldBorder)
    {
        fieldBorder->Highlight();
    }
    if (fieldTerrain)
    {
        fieldTerrain->Highlight();
    }
    if (fieldIceBlock)
    {
        fieldIceBlock->Highlight();
    }
    if (unitOnField)
    {
        unitOnField->GetRenderingObject()->Highlight();
    }
}

void Field::UnhighlightField() const
{
    if (fieldBorder)
    {
        fieldBorder->Unhighlight();
    }
    if (fieldTerrain)
    {
        fieldTerrain->Unhighlight();
    }
    if (fieldIceBlock)
    {
        fieldIceBlock->Unhighlight();
    }
    if (unitOnField)
    {
        unitOnField->GetRenderingObject()->Unhighlight();
    }
}

void Field::HalflightField() const
{
    if (fieldBorder)
    {
        fieldBorder->Halflight();
    }
    if (fieldTerrain)
    {
        fieldTerrain->Halflight();
    }
    if (fieldIceBlock)
    {
        fieldIceBlock->Halflight();
    }
    if (unitOnField)
    {
        unitOnField->GetRenderingObject()->Halflight();
    }
}

void Field::UnhalflightField() const
{
    if (fieldBorder)
    {
        fieldBorder->Unhalflight();
    }
    if (fieldTerrain)
    {
        fieldTerrain->Unhalflight();
    }
    if (fieldIceBlock)
    {
        fieldIceBlock->Unhalflight();
    }
    if (unitOnField)
    {
        unitOnField->GetRenderingObject()->Unhalflight();
    }
}

