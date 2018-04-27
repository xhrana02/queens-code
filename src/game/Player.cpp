//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
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
	default:
		throw exception("Player CTOR - Unknown player ID.");
	}
}

/**
 * \brief Decodes player's type from a code.
 * \param code Player's type encoded as integer.
 */
void Player::DecodePlayerType(int code)
{
	auto lastDigit = code % 10;
	if (lastDigit > 0){
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

	playerType = Human;
	aiType = None;
}

void Player::AddNewUnit(Unit* newUnit)
{
	units.push_back(newUnit);
	newUnit->SetOwner(id);
	newUnit->GetRenderingObject()->SetColors(normalColor, halflightColor, highlightColor);
}

void Player::AddNewUnitAndCreateUI(Unit* newUnit, Game* game, QQmlEngine* engine, QQuickItem* guiRoot)
{
	AddNewUnit(newUnit);
	newUnit->SetAppControl(appControl);
	newUnit->CreateInfoBar(engine, guiRoot);
	newUnit->CreateAbilitiesBar(engine, guiRoot);
	for (auto ability : newUnit->GetAbilites())
	{
		ability->SetGame(game);
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
		game->SelectUnit(units.front());
		appControl->OnTurnBegin();
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
