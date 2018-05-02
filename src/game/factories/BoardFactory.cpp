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

shared_ptr<Board> BoardFactory::CreateStandardBoard(ModelLoader* modelLoader)
{
	auto newBoard = make_shared<Board>(15, 15);

	auto throneObject = make_shared<RenderingObject>(modelLoader->GetModel("Throne"));
	throneObject->TextureRepeat = 10;
	newBoard->GetField(8, 8)->SetFieldTerrainObject(throneObject);
	newBoard->GetField(8, 8)->SetTerrainType(Throne);

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
		auto newWallObject = make_shared<RenderingObject>(modelLoader->GetModel("StoneWall"));
		newWallObject->position = vec3(field->GetRenderingPosX(), 0.0f, field->GetRenderingPosZ());
		field->SetFieldTerrainObject(newWallObject);
		field->SetTerrainType(Wall);
	}

	for (auto x = 1; x <= newBoard->PlayableWidth(); x++)
	{
		for (auto y = 1; y <= newBoard->PlayableHeight(); y++)
		{
			auto field = newBoard->GetField(x, y);
			auto newBorderObject = make_shared<RenderingObject>(modelLoader->GetModel("FieldBorder"));
			newBorderObject->position = vec3(field->GetRenderingPosX(), 0.0f, field->GetRenderingPosZ());
			newBorderObject->SetColors(BORDER_NORMAL_COLOR, BORDER_HALFLIGHT_COLOR, BORDER_HIGHLIGHT_COLOR);
			field->SetFieldBorderObject(newBorderObject);
		}
	}
	return newBoard;
}

shared_ptr<Board> BoardFactory::CreateTrainingDuelBoard(ModelLoader* modelLoader)
{
	auto newBoard = make_shared<Board>(5, 12);
	
	for (auto x = 1; x <= newBoard->PlayableWidth(); x++)
	{
		for (auto y = 1; y <= newBoard->PlayableHeight(); y++)
		{
			auto field = newBoard->GetField(x, y);
			auto newBorderObject = make_shared<RenderingObject>(modelLoader->GetModel("FieldBorder"));
			newBorderObject->position = vec3(field->GetRenderingPosX(), 0.0f, field->GetRenderingPosZ());
			newBorderObject->SetColors(BORDER_NORMAL_COLOR, BORDER_HALFLIGHT_COLOR, BORDER_HIGHLIGHT_COLOR);
			field->SetFieldBorderObject(newBorderObject);
		}
	}
	return newBoard;
}

shared_ptr<Board> BoardFactory::CreateChessBoard(ModelLoader* modelLoader)
{
	auto newBoard = make_shared<Board>(8, 8);

	for (auto x = 1; x <= newBoard->PlayableWidth(); x++)
	{
		for (auto y = 1; y <= newBoard->PlayableHeight(); y++)
		{
			auto field = newBoard->GetField(x, y);
			auto newBorderObject = make_shared<RenderingObject>(modelLoader->GetModel("FieldBorder"));
			newBorderObject->position = vec3(field->GetRenderingPosX(), 0.0f, field->GetRenderingPosZ());
			newBorderObject->SetColors(BORDER_NORMAL_COLOR, BORDER_HALFLIGHT_COLOR, BORDER_HIGHLIGHT_COLOR);
			field->SetFieldBorderObject(newBorderObject);
		}
	}
	return newBoard;
}
