//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "AiBoard.h"
#include "AiGame.h"
#include "AiUnit.h"
#include "IceBlock.h"

AiBoard::AiBoard(Board* source, AiGame* aiGame)
	: Board(source->PlayableWidth(), source->PlayableHeight())
{
	SetThroneField(source->GetThroneField()->GetX(), source->GetThroneField()->GetY());
	for (auto x = 1; x <= PlayableWidth(); x++)
	{
		for (auto y = 1; y <= PlayableHeight(); y++)
		{
			CopyField(source->GetField(x, y), fields[x][y], aiGame);
		}
	}
}

void AiBoard::CopyField(Field* source, Field* target, AiGame* aiGame) const
{
	target->SetFieldIceBlockUnit(std::make_shared<IceBlock>(), false);
	target->SetTerrainType(source->GetTerrainType());
	auto sourceUnit = source->GetPlayerUnitOnField();
	if (sourceUnit != nullptr)
	{
		auto unitCopy = new AiUnit(sourceUnit);
		aiGame->GetPlayerByID(sourceUnit->GetOwnerID())->AddNewUnit(unitCopy);
		target->MoveUnitToThisField(unitCopy);
	}
	if (source->IsFieldFrozen())
	{
		target->FreezeField();
	}

}
