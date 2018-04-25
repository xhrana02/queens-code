//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "BoardFactory.h"

using namespace fsg;
using namespace std;
using namespace glm;

Board* BoardFactory::CreateStandardBoard(ModelLoader* modelLoader)
{
	auto newBoard = new Board(15, 15);

	auto throneObject = make_shared<RenderingObject>(modelLoader->GetModel("Throne"));
	throneObject->TextureRepeat = 10;
	throneObject->SetColors(vec4(0.85f, 0.85f, 0.85f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	newBoard->GetField(8, 8)->SetFieldTerrainObject(throneObject);

	auto positionModifierX = (newBoard->PlayableWidth() + 1) / 2;
	auto positionModifierY = (newBoard->PlayableHeight() + 1) / 2;

	vector<Field*> wallFields;
	// bottom left corner
	wallFields.push_back(newBoard->GetField(5, 5));
	wallFields.push_back(newBoard->GetField(5, 6));
	wallFields.push_back(newBoard->GetField(6, 5));
	// top left corner
	wallFields.push_back(newBoard->GetField(5, 10));
	wallFields.push_back(newBoard->GetField(5, 11));
	wallFields.push_back(newBoard->GetField(6, 11));
	// bottom right corner
	wallFields.push_back(newBoard->GetField(10, 5));
	wallFields.push_back(newBoard->GetField(11, 5));
	wallFields.push_back(newBoard->GetField(11, 6));
	// top right corner
	wallFields.push_back(newBoard->GetField(10, 11));
	wallFields.push_back(newBoard->GetField(11, 10));
	wallFields.push_back(newBoard->GetField(11, 11));

	for (auto field : wallFields)
	{
		field->SetTerrainType(Wall);
		auto newWallObject = make_shared<RenderingObject>(modelLoader->GetModel("StoneWall"));
		newWallObject->position = vec3(field->GetX() - positionModifierX, 0.0f, field->GetY() - positionModifierY);
		newWallObject->SetColors(vec4(0.85f, 0.85f, 0.85f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f));
		field->SetFieldTerrainObject(newWallObject);
	}

	for (auto x = 1; x <= newBoard->PlayableWidth(); x++)
	{
		for (auto y = 1; y <= newBoard->PlayableHeight(); y++)
		{
			auto field = newBoard->GetField(x, y);
			auto newBorderObject = make_shared<RenderingObject>(modelLoader->GetModel("FieldBorder"));
			newBorderObject->position = vec3(field->GetX() - positionModifierX, 0.0f, field->GetY() - positionModifierY);
			newBorderObject->SetColors(BORDER_NORMAL_COLOR, BORDER_HIGHLIGHT_COLOR);
			field->SetFieldBorderObject(newBorderObject);
		}
	}
	return newBoard;
}
