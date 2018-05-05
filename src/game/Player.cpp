﻿//----------------------------------------------//
//  Author: Pavel Hranáč (xhrana02)             //
//  School: Vysoké učení technické v Brně       //
//  Faculty: Fakulta informačních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Player.h"
#include "Game.h"
#include "../ApplicationControl.h"

using namespace std;
using namespace fsg;

Player::~Player()
{
    for (auto unit : units)
    {
        delete unit;
    }
    for (auto unit : deadUnits)
    {
        delete unit;
    }
}

/**
 * \brief Player constructor.
 * \param inName Player inName.
 * \param inCode Player inCode.
 */
Player::Player(ApplicationControl* inAppControl, Game* inGame, PlayerID inID, QString inName, int inCode)
{
    appControl = inAppControl;
    game = inGame;
    id = inID;
    name = inName;
    DecodePlayerType(inCode);
    switch (id)
    {
    case Player1:
        normalColor = PLAYER1_NORMAL_COLOR;
        halflightColor = PLAYER1_HALFLIGHT_COLOR;
        highlightColor = PLAYER1_HIGHLIGHT_COLOR;
        break;
    case Player2:
        normalColor = PLAYER2_NORMAL_COLOR;
        halflightColor = PLAYER2_HALFLIGHT_COLOR;
        highlightColor = PLAYER2_HIGHLIGHT_COLOR;
        break;
    case Neutral:
        normalColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        halflightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        highlightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        break;
    default:
        throw exception("Player CTOR - Unknown player ID.");
    }
}

void Player::GamePopup(QString message) const
{
    if (appControl != nullptr)
    {
        appControl->ConsoleWrite(message);
        appControl->GamePopup(message);
    }
}

Player* Player::GetEnemyPlayer()
{
    return game->GetEnemyPlayer(this);
}

vector<Player*> Player::GetAllEnemyPlayers()
{
    return game->GetAllEnemyPlayers(this);
}

/**
 * \brief Decodes player's type from a code.
 * \param code Player's type encoded as integer.
 */
void Player::DecodePlayerType(int code)
{
    if (code < 0)
    {
        playerType = NeutralType;
        aiType = None;
        return;
    }

    auto lastDigit = code % 10;
    if (lastDigit == 0)
    {
        playerType = Human;
        aiType = None;
        return;
    }

    playerType = AI;
    switch(lastDigit)
    {
    case 1:
        aiType = Easy;
        return;
    case 2:
        aiType = Normal;
        return;
    case 3:
        aiType = Hard;
        return;
    case 4:
        aiType = Custom;
        return;
    default: 
        throw exception("Player.DecodePlayerType: Invalid player code.");
    }
}

void Player::AddNewUnit(Unit* newUnit)
{
    units.insert(newUnit);
    newUnit->SetOwner(this);
    newUnit->SetAppControl(appControl);
    for (auto ability : newUnit->GetAbilites())
    {
        ability->SetGame(game);
    }
}

void Player::AddNewUnitAndCreateUI(Unit* newUnit, QQmlEngine* engine, QQuickItem* guiRoot)
{
    AddNewUnit(newUnit);
    newUnit->GetRenderingObject()->SetColors(normalColor, halflightColor, highlightColor);
    newUnit->CreateInfoBar(engine, guiRoot);
    newUnit->CreateAbilitiesBar(engine, guiRoot);
}

void Player::OnUnitDeath(Unit* dyingUnit)
{
    units.erase(dyingUnit);
    deadUnits.insert(dyingUnit);

    if (game->IsRealGame())
    {
        GamePopup(name + "'s " + dyingUnit->GetName() + " died");
    }
    
    if (dyingUnit->IsRoyalty)
    {
        // if the player's queen died
        game->PlayerDefeat(this);
    }
    else if (units.size() <= 1)
    {
        // or if the queen is the last unit the player has
        game->PlayerDefeat(this);
    }
}

void Player::BeginTurn()
{
    for (auto unit : units)
    {
        unit->OnTurnBegin();
    }
    commandPoints = 3;
    game->SetActivePlayer(this);
    if (game->IsRealGame())
    {
        game->UnselectUnit();
        game->SelectUnit(*units.begin());
        appControl->OnTurnBegin(game->GetTurnNumber());
        GamePopup(name + "'s turn");
        appControl->SetActivePlayer(name);
    }
}

/**
 * \brief Returns true if this command ended this player's turn. Returns false otherwise.
 */
void Player::OnAbilityUsed()
{
    commandPoints--;
    if (game->IsRealGame())
    {
        appControl->OnAbilityUsed();
    }
}

bool Player::IsOutOfCommandPoints() const
{
    if(commandPoints <= 0)
    {
        return true;
    }
    return false;
}

void Player::EndTurn()
{
    for (auto unit : units)
    {
        unit->OnTurnEnd();
    }
    game->GetNextPlayer()->BeginTurn();
}
