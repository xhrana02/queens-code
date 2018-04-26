//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "GameFactory.h"
#include "BoardFactory.h"
#include "Queen.h"

using namespace fsg;
using namespace std;
using namespace glm;

Game* GameFactory::CreateStandardGame(Player* player_1, Player* player_2, ModelLoader* modelLoader, QQmlEngine* engine, QQuickItem* guiRoot)
{
	modelLoader->LoadModel(APP_RESOURCES"/models/StandardGround/StandardGround.obj", "StandardGround");
	modelLoader->LoadModel(APP_RESOURCES"/models/FieldBorder/FieldBorder.obj", "FieldBorder");
	modelLoader->LoadModel(APP_RESOURCES"/models/StoneWall/StoneWall.obj", "StoneWall");
	modelLoader->LoadModel(APP_RESOURCES"/models/Throne/Throne.obj", "Throne");
	modelLoader->LoadModel(APP_RESOURCES"/models/UnitQueen/UnitQueen.obj", "UnitQueen");

	auto newGame = new Game(player_1, player_2, BoardFactory::CreateStandardBoard(modelLoader));

	auto groundRO = make_shared<RenderingObject>(modelLoader->GetModel("StandardGround"));
	groundRO->TextureRepeat = 5;
	newGame->AddEnvironmentObject(groundRO);

	// PLAYER 1 UNITS
	auto p1Color = vec4(0.75f, 0.1f, 0.1f, 1.0f);
	auto p1HighlightColor = vec4(0.9f, 0.2f, 0.2f, 1.0f);

	vector<Unit*> p1Units;

	// QUEEN
	auto p1Queen = new Queen();
	p1Queen->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitQueen")));
	p1Units.push_back(p1Queen);

	// PLAYER 1 UNITS COMMON COMMANDS
	for (auto unit : p1Units)
	{
		unit->GetRenderingObject()->SetColors(p1Color, p1HighlightColor);
		unit->CreateInfoBar(engine, guiRoot);
		unit->CreateAbilitiesBar(engine, guiRoot);
		player_1->AddNewUnit(unit);
		for (auto ability : unit->GetAbilites())
		{
			ability->SetGame(newGame);
		}
	}

	// PLAYER 1 UNITS POSITIONS
	newGame->GetGameBoard()->GetPlayField(8, 1)->MoveUnitToThisField(p1Queen);

	// PLAYER 2 UNITS
	auto p2Color = vec4(0.2f, 0.2f, 0.8f, 1.0f);
	auto p2HighlightColor = vec4(0.3f, 0.3f, 0.95f, 1.0f);
	auto p2Rotation = 180.0f;

	vector<Unit*> p2Units;

	// QUEEN
	auto p2Queen = new Queen();
	p2Queen->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitQueen")));
	p2Units.push_back(p2Queen);

	// PLAYER 2 UNITS COMMON COMMANDS
	for (auto unit : p2Units)
	{
		unit->GetRenderingObject()->SetColors(p2Color, p2HighlightColor);
		unit->GetRenderingObject()->rotation = p2Rotation;
		unit->CreateInfoBar(engine, guiRoot);
		unit->CreateAbilitiesBar(engine, guiRoot);
		player_2->AddNewUnit(unit);
		for (auto ability : unit->GetAbilites())
		{
			ability->SetGame(newGame);
		}
	}

	// PLAYER 2 UNITS POSITIONS
	newGame->GetGameBoard()->GetPlayField(8, 15)->MoveUnitToThisField(p2Queen);

	return newGame;
}
