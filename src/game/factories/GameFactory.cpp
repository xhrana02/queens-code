//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
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

	// QUEEN
	auto p1Queen = new Queen();
	auto p1QueenRO = make_shared<RenderingObject>(modelLoader->GetModel("UnitQueen"));
	p1QueenRO->SetColors(p1Color, p1HighlightColor);
	p1Queen->SetRenderingObject(p1QueenRO);
	p1Queen->CreateInfoBar(engine, guiRoot);
	newGame->GetGameBoard()->GetPlayField(8, 1)->MoveUnitToThisField(p1Queen);
	player_1->AddNewUnit(p1Queen);

	// PLAYER 2 UNITS
	auto p2Color = vec4(0.2f, 0.2f, 0.8f, 1.0f);
	auto p2HighlightColor = vec4(0.3f, 0.3f, 0.95f, 1.0f);
	auto p2Rotation = 180.0f;

	// QUEEN
	auto p2Queen = new Queen();
	auto p2QueenRO = make_shared<RenderingObject>(modelLoader->GetModel("UnitQueen"));
	p2QueenRO->SetColors(p2Color, p2HighlightColor);
	p2QueenRO->rotation = p2Rotation;
	p2Queen->SetRenderingObject(p2QueenRO);
	p2Queen->CreateInfoBar(engine, guiRoot);
	newGame->GetGameBoard()->GetPlayField(8, 15)->MoveUnitToThisField(p2Queen);
	player_2->AddNewUnit(p2Queen);

	return newGame;
}
