//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "BoardFactory.h"

Board* BoardFactory::CreateStandardBoard(ModelLoader* modelLoader)
{
	auto newBoard = new Board(15, 15);

	// bottom left corner
	newBoard->GetField(5, 5)->SetTerrainType(Wall);
	newBoard->GetField(5, 6)->SetTerrainType(Wall);
	newBoard->GetField(6, 5)->SetTerrainType(Wall);

	// top left corner
	newBoard->GetField(5, 11)->SetTerrainType(Wall);
	newBoard->GetField(5, 10)->SetTerrainType(Wall);
	newBoard->GetField(6, 11)->SetTerrainType(Wall);

	// bottom right corner
	newBoard->GetField(11, 5)->SetTerrainType(Wall);
	newBoard->GetField(10, 5)->SetTerrainType(Wall);
	newBoard->GetField(11, 6)->SetTerrainType(Wall);

	// top right corner
	newBoard->GetField(11, 11)->SetTerrainType(Wall);
	newBoard->GetField(10, 11)->SetTerrainType(Wall);
	newBoard->GetField(11, 10)->SetTerrainType(Wall);

	auto positionModifierX = (newBoard->PlayableWidth() - 1) / 2;
	auto positionModifierY = (newBoard->PlayableHeight() - 1) / 2;
	for (auto x = 0; x < newBoard->PlayableWidth(); x++)
	{
		for (auto y = 0; y < newBoard->PlayableHeight(); y++)
		{
			auto newField = make_shared<RenderingObject>(modelLoader->GetModel("FieldBorder"));
			newField->SetPosition(vec3(x - positionModifierX, 0.0f, y - positionModifierY));
			newField->SetColor(vec4(0.94f, 0.89f, 0.66f, 1.0f));
			newField->SetHighlightColor(vec4(0.97f, 0.94f, 0.83f, 0.5f));
			newBoard->GetField(x+1, y+1)->SetFieldBorderObject(newField);
		}
	}
	return newBoard;
}
