//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "GameFactory.h"
#include "BoardFactory.h"
#include "Cursor.h"
#include "Queen.h"
#include "Knight.h"
#include "Spearman.h"
#include "Ranger.h"
#include "Brute.h"
#include "Scout.h"
#include "Agent.h"
#include "Priest.h"
#include "Warlock.h"
#include "Wizard.h"

using namespace fsg;
using namespace std;
using namespace glm;

Game* GameFactory::CreateStandardGame(ApplicationControl* appControl,
	QString p1Name, int p1Code, QString p2Name, int p2Code,
	ModelLoader* modelLoader, QQmlEngine* engine, QQuickItem* guiRoot)
{
	modelLoader->LoadModel(APP_RESOURCES"/models/Cursor/Cursor.obj", "Cursor");
	modelLoader->LoadModel(APP_RESOURCES"/models/StandardGround/StandardGround.obj", "StandardGround");
	modelLoader->LoadModel(APP_RESOURCES"/models/FieldBorder/FieldBorder.obj", "FieldBorder");
	modelLoader->LoadModel(APP_RESOURCES"/models/StoneWall/StoneWall.obj", "StoneWall");
	modelLoader->LoadModel(APP_RESOURCES"/models/Throne/Throne.obj", "Throne");
	modelLoader->LoadModel(APP_RESOURCES"/models/UnitQueen/UnitQueen.obj", "UnitQueen");
	modelLoader->LoadModel(APP_RESOURCES"/models/UnitKnight/UnitKnight.obj", "UnitKnight");
	modelLoader->LoadModel(APP_RESOURCES"/models/UnitSpearman/UnitSpearman.obj", "UnitSpearman");
	modelLoader->LoadModel(APP_RESOURCES"/models/UnitBrute/UnitBrute.obj", "UnitBrute");
	modelLoader->LoadModel(APP_RESOURCES"/models/UnitRanger/UnitRanger.obj", "UnitRanger");
	modelLoader->LoadModel(APP_RESOURCES"/models/UnitScout/UnitScout.obj", "UnitScout");
	modelLoader->LoadModel(APP_RESOURCES"/models/UnitAgent/UnitAgent.obj", "UnitAgent");
	modelLoader->LoadModel(APP_RESOURCES"/models/UnitWarlock/UnitWarlock.obj", "UnitWarlock");
	modelLoader->LoadModel(APP_RESOURCES"/models/UnitPriest/UnitPriest.obj", "UnitPriest");
	modelLoader->LoadModel(APP_RESOURCES"/models/UnitWizard/UnitWizard.obj", "UnitWizard");

	auto newGame = new Game(appControl, BoardFactory::CreateStandardBoard(modelLoader));
	newGame->ThisIsRealGame();
	newGame->AddPlayer(make_shared<Player>(appControl, newGame, Player1, p1Name, p1Code));
	newGame->AddPlayer(make_shared<Player>(appControl, newGame, Player2, p2Name, p2Code));
	newGame->AddCursor(make_shared<Cursor>(make_shared<RenderingObject>(modelLoader->GetModel("Cursor"))));

	auto groundRO = make_shared<RenderingObject>(modelLoader->GetModel("StandardGround"));
	groundRO->TextureRepeat = 5;
	newGame->AddEnvironmentObject(groundRO);

	////////////////////////////////////////////////////////////////////////////////
	// PLAYER 1 UNITS
	auto p1Queen = new Queen();
	p1Queen->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitQueen")));
	auto p1Knight = new Knight();
	p1Knight->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitKnight")));
	auto p1Spearman = new Spearman();
	p1Spearman->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitSpearman")));
	auto p1Brute = new Brute();
	p1Brute->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitBrute")));
	auto p1Ranger = new Ranger();
	p1Ranger->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitRanger")));
	auto p1Scout = new Scout();
	p1Scout->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitScout")));
	auto p1Agent = new Agent();
	p1Agent->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitAgent")));
	auto p1Warlock = new Warlock();
	p1Warlock->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitWarlock")));
	auto p1Priest = new Priest();
	p1Priest->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitPriest")));
	auto p1Wizard = new Wizard();
	p1Wizard->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitWizard")));
	// PLAYER 1 UNITS COMMON COMMANDS
	vector<Unit*> p1Units;
	p1Units.push_back(p1Queen);
	p1Units.push_back(p1Knight);
	p1Units.push_back(p1Spearman);
	p1Units.push_back(p1Brute);
	p1Units.push_back(p1Ranger);
	p1Units.push_back(p1Scout);
	p1Units.push_back(p1Agent);
	p1Units.push_back(p1Warlock);
	p1Units.push_back(p1Priest);
	p1Units.push_back(p1Wizard);
	for (auto unit : p1Units)
	{
		newGame->GetPlayer1()->AddNewUnitAndCreateUI(unit, newGame, engine, guiRoot);
	}
	// PLAYER 1 UNITS POSITIONS
	newGame->GetGameBoard()->GetPlayField(8, 1)->MoveUnitToThisField(p1Queen);
	newGame->GetGameBoard()->GetPlayField(8, 2)->MoveUnitToThisField(p1Knight);
	newGame->GetGameBoard()->GetPlayField(9, 2)->MoveUnitToThisField(p1Spearman);
	newGame->GetGameBoard()->GetPlayField(7, 2)->MoveUnitToThisField(p1Brute);
	newGame->GetGameBoard()->GetPlayField(10, 1)->MoveUnitToThisField(p1Ranger);
	newGame->GetGameBoard()->GetPlayField(10, 2)->MoveUnitToThisField(p1Scout);
	newGame->GetGameBoard()->GetPlayField(6, 2)->MoveUnitToThisField(p1Agent);
	newGame->GetGameBoard()->GetPlayField(6, 1)->MoveUnitToThisField(p1Warlock);
	newGame->GetGameBoard()->GetPlayField(9, 1)->MoveUnitToThisField(p1Priest);
	newGame->GetGameBoard()->GetPlayField(7, 1)->MoveUnitToThisField(p1Wizard);

	////////////////////////////////////////////////////////////////////////////////
	// PLAYER 2 UNITS
	auto p2Queen = new Queen();
	p2Queen->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitQueen")));
	auto p2Knight = new Knight();
	p2Knight->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitKnight")));
	auto p2Spearman = new Spearman();
	p2Spearman->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitSpearman")));
	auto p2Brute = new Brute();
	p2Brute->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitBrute")));
	auto p2Ranger = new Ranger();
	p2Ranger->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitRanger")));
	auto p2Scout = new Scout();
	p2Scout->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitScout")));
	auto p2Agent = new Agent();
	p2Agent->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitAgent")));
	auto p2Warlock = new Warlock();
	p2Warlock->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitWarlock")));
	auto p2Priest = new Priest();
	p2Priest->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitPriest")));
	auto p2Wizard = new Wizard();
	p2Wizard->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitWizard")));
	// PLAYER 2 UNITS COMMON COMMANDS
	auto p2Rotation = 180.0f;
	vector<Unit*> p2Units;
	p2Units.push_back(p2Queen);
	p2Units.push_back(p2Knight);
	p2Units.push_back(p2Spearman);
	p2Units.push_back(p2Brute);
	p2Units.push_back(p2Ranger);
	p2Units.push_back(p2Scout);
	p2Units.push_back(p2Agent);
	p2Units.push_back(p2Warlock);
	p2Units.push_back(p2Priest);
	p2Units.push_back(p2Wizard);
	for (auto unit : p2Units)
	{
		unit->GetRenderingObject()->rotation = p2Rotation;
		newGame->GetPlayer2()->AddNewUnitAndCreateUI(unit, newGame, engine, guiRoot);
	}
	// PLAYER 2 UNITS POSITIONS
	newGame->GetGameBoard()->GetPlayField(8, 15)->MoveUnitToThisField(p2Queen);
	newGame->GetGameBoard()->GetPlayField(8, 14)->MoveUnitToThisField(p2Knight);
	newGame->GetGameBoard()->GetPlayField(7, 14)->MoveUnitToThisField(p2Spearman);
	newGame->GetGameBoard()->GetPlayField(9, 14)->MoveUnitToThisField(p2Brute);
	newGame->GetGameBoard()->GetPlayField(6, 15)->MoveUnitToThisField(p2Ranger);
	newGame->GetGameBoard()->GetPlayField(6, 14)->MoveUnitToThisField(p2Scout);
	newGame->GetGameBoard()->GetPlayField(10, 14)->MoveUnitToThisField(p2Agent);
	newGame->GetGameBoard()->GetPlayField(10, 15)->MoveUnitToThisField(p2Warlock);
	newGame->GetGameBoard()->GetPlayField(7, 15)->MoveUnitToThisField(p2Priest);
	newGame->GetGameBoard()->GetPlayField(9, 15)->MoveUnitToThisField(p2Wizard);


	return newGame;
}
