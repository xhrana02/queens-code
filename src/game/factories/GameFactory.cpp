//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//    School: Vysoké uèení technické v Brnì        //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "GameFactory.h"
#include "../../ApplicationControl.h"
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

Game* GameFactory::CreateStandardGame(QString p1Name, int p1Code, QString p2Name, int p2Code,
    ApplicationControl* appControl, ModelLoader* modelLoader, QQmlEngine* engine, QQuickItem* guiRoot)
{
    modelLoader->LoadModel(APP_RESOURCES"/models/Cursor/Cursor.obj", "Cursor");
    appControl->UpdateLoadingProgress(0.01f);
    modelLoader->LoadModel(APP_RESOURCES"/models/StandardGround/StandardGround.obj", "StandardGround");
    appControl->UpdateLoadingProgress(0.10f);
    modelLoader->LoadModel(APP_RESOURCES"/models/UnitQueen/UnitQueen.obj", "UnitQueen");
    appControl->UpdateLoadingProgress(0.18f);
    modelLoader->LoadModel(APP_RESOURCES"/models/UnitKnight/UnitKnight.obj", "UnitKnight");
    appControl->UpdateLoadingProgress(0.26f);
    modelLoader->LoadModel(APP_RESOURCES"/models/UnitSpearman/UnitSpearman.obj", "UnitSpearman");
    appControl->UpdateLoadingProgress(0.34f);
    modelLoader->LoadModel(APP_RESOURCES"/models/UnitBrute/UnitBrute.obj", "UnitBrute");
    appControl->UpdateLoadingProgress(0.42f);
    modelLoader->LoadModel(APP_RESOURCES"/models/UnitRanger/UnitRanger.obj", "UnitRanger");
    appControl->UpdateLoadingProgress(0.50f);
    modelLoader->LoadModel(APP_RESOURCES"/models/UnitScout/UnitScout.obj", "UnitScout");
    appControl->UpdateLoadingProgress(0.58f);
    modelLoader->LoadModel(APP_RESOURCES"/models/UnitAgent/UnitAgent.obj", "UnitAgent");
    appControl->UpdateLoadingProgress(0.66f);
    modelLoader->LoadModel(APP_RESOURCES"/models/UnitWarlock/UnitWarlock.obj", "UnitWarlock");
    appControl->UpdateLoadingProgress(0.74f);
    modelLoader->LoadModel(APP_RESOURCES"/models/UnitPriest/UnitPriest.obj", "UnitPriest");
    appControl->UpdateLoadingProgress(0.82f);
    modelLoader->LoadModel(APP_RESOURCES"/models/UnitWizard/UnitWizard.obj", "UnitWizard");
    appControl->UpdateLoadingProgress(0.90f);

    auto newGame = new Game(appControl);
    newGame->SetGameBoard(BoardFactory::CreateStandardBoard(modelLoader));
    newGame->ThisIsRealGame();
    newGame->AddPlayer(make_shared<Player>(appControl, newGame, Player1, p1Name, Player::DecodeAiType(p1Code)));
    newGame->AddPlayer(make_shared<Player>(appControl, newGame, Player2, p2Name, Player::DecodeAiType(p2Code)));
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
        newGame->GetPlayer1()->AddNewUnitAndCreateUI(unit, engine, guiRoot);
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
        newGame->GetPlayer2()->AddNewUnitAndCreateUI(unit, engine, guiRoot);
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

    appControl->UpdateLoadingProgress(0.99f);
    return newGame;
}

////////////////////////////////////////////////////////////////////////////////
// SCENARIO GAMES

Game* GameFactory::CreateScenarioGame(QString scenarioName,
    ApplicationControl* appControl, ModelLoader* modelLoader, QQmlEngine* engine, QQuickItem* guiRoot)
{
    if (scenarioName == "Training Duel")
    {
        return CreateTrainingDuel(appControl, modelLoader, engine, guiRoot);
    }

    if (scenarioName == "Chess")
    {
        return CreateChess(appControl, modelLoader, engine, guiRoot);
    }

    throw exception("GameFactory CreateScenarioGame - Unknown scenario.");
}

Game* GameFactory::CreateTrainingDuel(ApplicationControl* appControl, ModelLoader* modelLoader, QQmlEngine* engine, QQuickItem* guiRoot)
{
    modelLoader->LoadModel(APP_RESOURCES"/models/Cursor/Cursor.obj", "Cursor");
    appControl->UpdateLoadingProgress(0.01f);
    modelLoader->LoadModel(APP_RESOURCES"/models/StandardGround/StandardGround.obj", "StandardGround");
    appControl->UpdateLoadingProgress(0.30f);
    modelLoader->LoadModel(APP_RESOURCES"/models/UnitKnight/UnitKnight.obj", "UnitKnight");
    appControl->UpdateLoadingProgress(0.60f);
    modelLoader->LoadModel(APP_RESOURCES"/models/UnitSpearman/UnitSpearman.obj", "UnitSpearman");
    appControl->UpdateLoadingProgress(0.90f);

    auto newGame = new Game(appControl);
    newGame->SetGameBoard(BoardFactory::CreateTrainingDuelBoard(modelLoader));
    newGame->ThisIsRealGame();
    newGame->AddPlayer(make_shared<Player>(appControl, newGame, Player1, "Player", Human));
    newGame->AddPlayer(make_shared<Player>(appControl, newGame, Player2, "Training AI", Easy));
    newGame->AddCursor(make_shared<Cursor>(make_shared<RenderingObject>(modelLoader->GetModel("Cursor"))));

    auto groundRO = make_shared<RenderingObject>(modelLoader->GetModel("StandardGround"));
    groundRO->TextureRepeat = 5;
    newGame->AddEnvironmentObject(groundRO);

    ////////////////////////////////////////////////////////////////////////////////
    // PLAYER 1 UNITS
    auto p1Knight = new Knight();
    p1Knight->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitKnight")));
    // PLAYER 1 UNITS COMMON COMMANDS
    vector<Unit*> p1Units;
    p1Units.push_back(p1Knight);
    for (auto unit : p1Units)
    {
        newGame->GetPlayer1()->AddNewUnitAndCreateUI(unit, engine, guiRoot);
    }
    // PLAYER 1 UNITS POSITIONS
    newGame->GetGameBoard()->GetPlayField(3, 2)->MoveUnitToThisField(p1Knight);

    ////////////////////////////////////////////////////////////////////////////////
    // PLAYER 2 UNITS
    auto p2Spearman = new Spearman();
    p2Spearman->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitSpearman")));
    // PLAYER 2 UNITS COMMON COMMANDS
    auto p2Rotation = 180.0f;
    vector<Unit*> p2Units;
    p2Units.push_back(p2Spearman);
    for (auto unit : p2Units)
    {
        unit->GetRenderingObject()->rotation = p2Rotation;
        newGame->GetPlayer2()->AddNewUnitAndCreateUI(unit, engine, guiRoot);
    }
    // PLAYER 2 UNITS POSITIONS
    newGame->GetGameBoard()->GetPlayField(3, 11)->MoveUnitToThisField(p2Spearman);

    appControl->UpdateLoadingProgress(0.99f);
    return newGame;
}

Game* GameFactory::CreateChess(ApplicationControl* appControl, ModelLoader* modelLoader, QQmlEngine* engine, QQuickItem* guiRoot)
{
    modelLoader->LoadModel(APP_RESOURCES"/models/Cursor/Cursor.obj", "Cursor");
    appControl->UpdateLoadingProgress(0.01f);
    modelLoader->LoadModel(APP_RESOURCES"/models/StandardGround/StandardGround.obj", "StandardGround");
    appControl->UpdateLoadingProgress(0.14f);
    modelLoader->LoadModel(APP_RESOURCES"/models/UnitQueen/UnitQueen.obj", "UnitQueen");
    appControl->UpdateLoadingProgress(0.25f);
    modelLoader->LoadModel(APP_RESOURCES"/models/UnitSpearman/UnitSpearman.obj", "UnitSpearman");
    appControl->UpdateLoadingProgress(0.38f);
    modelLoader->LoadModel(APP_RESOURCES"/models/UnitBrute/UnitBrute.obj", "UnitBrute");
    appControl->UpdateLoadingProgress(0.51f);
    modelLoader->LoadModel(APP_RESOURCES"/models/UnitAgent/UnitAgent.obj", "UnitAgent");
    appControl->UpdateLoadingProgress(0.64f);
    modelLoader->LoadModel(APP_RESOURCES"/models/UnitWarlock/UnitWarlock.obj", "UnitWarlock");
    appControl->UpdateLoadingProgress(0.77f);
    modelLoader->LoadModel(APP_RESOURCES"/models/UnitPriest/UnitPriest.obj", "UnitPriest");
    appControl->UpdateLoadingProgress(0.90f);

    auto newGame = new Game(appControl);
    newGame->SetGameBoard(BoardFactory::CreateChessBoard(modelLoader));
    newGame->ThisIsRealGame();
    newGame->AddPlayer(make_shared<Player>(appControl, newGame, Player1, "Player", Human));
    newGame->AddPlayer(make_shared<Player>(appControl, newGame, Player2, "Chess Master 5000", Hard));
    newGame->AddCursor(make_shared<Cursor>(make_shared<RenderingObject>(modelLoader->GetModel("Cursor"))));

    auto groundRO = make_shared<RenderingObject>(modelLoader->GetModel("StandardGround"));
    groundRO->TextureRepeat = 5;
    newGame->AddEnvironmentObject(groundRO);

    ////////////////////////////////////////////////////////////////////////////////
    // PLAYER 1 UNITS
    auto p1Queen = new Queen();
    p1Queen->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitQueen")));
    auto p1Warlock = new Warlock();
    p1Warlock->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitWarlock")));
    auto p1Brute1 = new Brute();
    p1Brute1->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitBrute")));
    auto p1Brute2 = new Brute();
    p1Brute2->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitBrute")));
    auto p1Priest1 = new Priest();
    p1Priest1->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitPriest")));
    auto p1Priest2 = new Priest();
    p1Priest2->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitPriest")));
    auto p1Agent1 = new Agent();
    p1Agent1->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitAgent")));
    auto p1Agent2 = new Agent();
    p1Agent2->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitAgent")));
    auto p1Spearman1 = new Spearman();
    p1Spearman1->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitSpearman")));
    auto p1Spearman2 = new Spearman();
    p1Spearman2->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitSpearman")));
    auto p1Spearman3 = new Spearman();
    p1Spearman3->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitSpearman")));
    auto p1Spearman4 = new Spearman();
    p1Spearman4->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitSpearman")));
    auto p1Spearman5 = new Spearman();
    p1Spearman5->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitSpearman")));
    auto p1Spearman6 = new Spearman();
    p1Spearman6->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitSpearman")));
    auto p1Spearman7 = new Spearman();
    p1Spearman7->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitSpearman")));
    auto p1Spearman8 = new Spearman();
    p1Spearman8->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitSpearman")));
    // PLAYER 1 UNITS COMMON COMMANDS
    vector<Unit*> p1Units;
    p1Units.push_back(p1Queen);
    p1Units.push_back(p1Warlock);
    p1Units.push_back(p1Brute1);
    p1Units.push_back(p1Brute2);
    p1Units.push_back(p1Agent1);
    p1Units.push_back(p1Agent2);
    p1Units.push_back(p1Priest1);
    p1Units.push_back(p1Priest2);
    p1Units.push_back(p1Spearman1);
    p1Units.push_back(p1Spearman2);
    p1Units.push_back(p1Spearman3);
    p1Units.push_back(p1Spearman4);
    p1Units.push_back(p1Spearman5);
    p1Units.push_back(p1Spearman6);
    p1Units.push_back(p1Spearman7);
    p1Units.push_back(p1Spearman8);
    for (auto unit : p1Units)
    {
        newGame->GetPlayer1()->AddNewUnitAndCreateUI(unit, engine, guiRoot);
    }
    // PLAYER 1 UNITS POSITIONS
    newGame->GetGameBoard()->GetPlayField(4, 1)->MoveUnitToThisField(p1Queen);
    newGame->GetGameBoard()->GetPlayField(5, 1)->MoveUnitToThisField(p1Warlock);
    newGame->GetGameBoard()->GetPlayField(1, 1)->MoveUnitToThisField(p1Brute1);
    newGame->GetGameBoard()->GetPlayField(8, 1)->MoveUnitToThisField(p1Brute2);
    newGame->GetGameBoard()->GetPlayField(3, 1)->MoveUnitToThisField(p1Priest1);
    newGame->GetGameBoard()->GetPlayField(6, 1)->MoveUnitToThisField(p1Priest2);
    newGame->GetGameBoard()->GetPlayField(2, 1)->MoveUnitToThisField(p1Agent1);
    newGame->GetGameBoard()->GetPlayField(7, 1)->MoveUnitToThisField(p1Agent2);
    newGame->GetGameBoard()->GetPlayField(1, 2)->MoveUnitToThisField(p1Spearman1);
    newGame->GetGameBoard()->GetPlayField(2, 2)->MoveUnitToThisField(p1Spearman2);
    newGame->GetGameBoard()->GetPlayField(3, 2)->MoveUnitToThisField(p1Spearman3);
    newGame->GetGameBoard()->GetPlayField(4, 2)->MoveUnitToThisField(p1Spearman4);
    newGame->GetGameBoard()->GetPlayField(5, 2)->MoveUnitToThisField(p1Spearman5);
    newGame->GetGameBoard()->GetPlayField(6, 2)->MoveUnitToThisField(p1Spearman6);
    newGame->GetGameBoard()->GetPlayField(7, 2)->MoveUnitToThisField(p1Spearman7);
    newGame->GetGameBoard()->GetPlayField(8, 2)->MoveUnitToThisField(p1Spearman8);

    ////////////////////////////////////////////////////////////////////////////////
    // PLAYER 2 UNITS
    auto p2Queen = new Queen();
    p2Queen->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitQueen")));
    auto p2Warlock = new Warlock();
    p2Warlock->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitWarlock")));
    auto p2Brute1 = new Brute();
    p2Brute1->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitBrute")));
    auto p2Brute2 = new Brute();
    p2Brute2->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitBrute")));
    auto p2Priest1 = new Priest();
    p2Priest1->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitPriest")));
    auto p2Priest2 = new Priest();
    p2Priest2->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitPriest")));
    auto p2Agent1 = new Agent();
    p2Agent1->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitAgent")));
    auto p2Agent2 = new Agent();
    p2Agent2->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitAgent")));
    auto p2Spearman1 = new Spearman();
    p2Spearman1->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitSpearman")));
    auto p2Spearman2 = new Spearman();
    p2Spearman2->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitSpearman")));
    auto p2Spearman3 = new Spearman();
    p2Spearman3->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitSpearman")));
    auto p2Spearman4 = new Spearman();
    p2Spearman4->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitSpearman")));
    auto p2Spearman5 = new Spearman();
    p2Spearman5->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitSpearman")));
    auto p2Spearman6 = new Spearman();
    p2Spearman6->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitSpearman")));
    auto p2Spearman7 = new Spearman();
    p2Spearman7->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitSpearman")));
    auto p2Spearman8 = new Spearman();
    p2Spearman8->SetRenderingObject(make_shared<RenderingObject>(modelLoader->GetModel("UnitSpearman")));
    // PLAYER 2 UNITS COMMON COMMANDS
    auto p2Rotation = 180.0f;
    vector<Unit*> p2Units;
    p2Units.push_back(p2Queen);
    p2Units.push_back(p2Warlock);
    p2Units.push_back(p2Brute1);
    p2Units.push_back(p2Brute2);
    p2Units.push_back(p2Agent1);
    p2Units.push_back(p2Agent2);
    p2Units.push_back(p2Priest1);
    p2Units.push_back(p2Priest2);
    p2Units.push_back(p2Spearman1);
    p2Units.push_back(p2Spearman2);
    p2Units.push_back(p2Spearman3);
    p2Units.push_back(p2Spearman4);
    p2Units.push_back(p2Spearman5);
    p2Units.push_back(p2Spearman6);
    p2Units.push_back(p2Spearman7);
    p2Units.push_back(p2Spearman8);
    for (auto unit : p2Units)
    {
        unit->GetRenderingObject()->rotation = p2Rotation;
        newGame->GetPlayer2()->AddNewUnitAndCreateUI(unit, engine, guiRoot);
    }
    // PLAYER 2 UNITS POSITIONS
    newGame->GetGameBoard()->GetPlayField(4, 8)->MoveUnitToThisField(p2Queen);
    newGame->GetGameBoard()->GetPlayField(5, 8)->MoveUnitToThisField(p2Warlock);
    newGame->GetGameBoard()->GetPlayField(1, 8)->MoveUnitToThisField(p2Brute1);
    newGame->GetGameBoard()->GetPlayField(8, 8)->MoveUnitToThisField(p2Brute2);
    newGame->GetGameBoard()->GetPlayField(3, 8)->MoveUnitToThisField(p2Priest1);
    newGame->GetGameBoard()->GetPlayField(6, 8)->MoveUnitToThisField(p2Priest2);
    newGame->GetGameBoard()->GetPlayField(2, 8)->MoveUnitToThisField(p2Agent1);
    newGame->GetGameBoard()->GetPlayField(7, 8)->MoveUnitToThisField(p2Agent2);
    newGame->GetGameBoard()->GetPlayField(1, 7)->MoveUnitToThisField(p2Spearman1);
    newGame->GetGameBoard()->GetPlayField(2, 7)->MoveUnitToThisField(p2Spearman2);
    newGame->GetGameBoard()->GetPlayField(3, 7)->MoveUnitToThisField(p2Spearman3);
    newGame->GetGameBoard()->GetPlayField(4, 7)->MoveUnitToThisField(p2Spearman4);
    newGame->GetGameBoard()->GetPlayField(5, 7)->MoveUnitToThisField(p2Spearman5);
    newGame->GetGameBoard()->GetPlayField(6, 7)->MoveUnitToThisField(p2Spearman6);
    newGame->GetGameBoard()->GetPlayField(7, 7)->MoveUnitToThisField(p2Spearman7);
    newGame->GetGameBoard()->GetPlayField(8, 7)->MoveUnitToThisField(p2Spearman8);

    appControl->UpdateLoadingProgress(0.99f);
    return newGame;
}
