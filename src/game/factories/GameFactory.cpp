//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "GameFactory.h"
#include "BoardFactory.h"
#include "Queen.h"
#include "Knight.h"

using namespace fsg;
using namespace std;
using namespace glm;

Game* GameFactory::CreateStandardGame(ApplicationControl* appControl,
	QString p1Name, int p1Code, QString p2Name, int p2Code,
	ModelLoader* modelLoader, QQmlEngine* engine, QQuickItem* guiRoot)
{
	modelLoader->LoadModel(APP_RESOURCES"/models/StandardGround/StandardGround.obj", "StandardGround");
	modelLoader->LoadModel(APP_RESOURCES"/models/FieldBorder/FieldBorder.obj", "FieldBorder");
	modelLoader->LoadModel(APP_RESOURCES"/models/StoneWall/StoneWall.obj", "StoneWall");
	modelLoader->LoadModel(APP_RESOURCES"/models/Throne/Throne.obj", "Throne");
	modelLoader->LoadModel(APP_RESOURCES"/models/UnitQueen/UnitQueen.obj", "UnitQueen");
	modelLoader->LoadModel(APP_RESOURCES"/models/UnitKnight/UnitKnight.obj", "UnitKnight");

	auto newGame = new Game(appControl, BoardFactory::CreateStandardBoard(modelLoader));
	newGame->ThisIsRealGame();
	newGame->AddPlayer(make_shared<Player>(appControl, newGame, Player1, p1Name, p1Code));
	newGame->AddPlayer(make_shared<Player>(appControl, newGame, Player2, p2Name, p2Code));

	auto groundRO = make_shared<RenderingObject>(modelLoader->GetModel("StandardGround"));
	groundRO->TextureRepeat = 5;
	newGame->AddEnvironmentObject(groundRO);

	////////////////////////////////////////////////////////////////////////////////
	// PLAYER 1 UNITS
	// QUEEN
	auto p1Queen = new Queen();
	p1Queen->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitQueen")));
	// KNIGHT
	auto p1Knight = new Knight();
	p1Knight->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitKnight")));
	// PLAYER 1 UNITS COMMON COMMANDS
	vector<Unit*> p1Units;
	p1Units.push_back(p1Queen);
	p1Units.push_back(p1Knight);
	for (auto unit : p1Units)
	{
		newGame->GetPlayer1()->AddNewUnitAndCreateUI(unit, newGame, engine, guiRoot);
	}
	// PLAYER 1 UNITS POSITIONS
	newGame->GetGameBoard()->GetPlayField(8, 1)->MoveUnitToThisField(p1Queen);
	newGame->GetGameBoard()->GetPlayField(8, 2)->MoveUnitToThisField(p1Knight);

	////////////////////////////////////////////////////////////////////////////////
	// PLAYER 2 UNITS
	// QUEEN
	auto p2Queen = new Queen();
	p2Queen->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitQueen")));
	auto p2Knight = new Knight();
	p2Knight->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitKnight")));

	// PLAYER 2 UNITS COMMON COMMANDS
	auto p2Rotation = 180.0f;
	vector<Unit*> p2Units;
	p2Units.push_back(p2Queen);
	p2Units.push_back(p2Knight);
	for (auto unit : p2Units)
	{
		unit->GetRenderingObject()->rotation = p2Rotation;
		newGame->GetPlayer2()->AddNewUnitAndCreateUI(unit, newGame, engine, guiRoot);
	}
	// PLAYER 2 UNITS POSITIONS
	newGame->GetGameBoard()->GetPlayField(8, 15)->MoveUnitToThisField(p2Queen);
	newGame->GetGameBoard()->GetPlayField(8, 14)->MoveUnitToThisField(p2Knight);


	return newGame;
}
