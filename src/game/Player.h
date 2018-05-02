//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "GameEnums.h"
#include "Unit.h"
#include <QObject>
#include <set>

#define PLAYER1_NORMAL_COLOR glm::vec4(0.19f, 0.21f, 0.85f, 1.0f)
#define PLAYER1_HALFLIGHT_COLOR glm::vec4(0.21f, 0.85f, 0.85f, 1.0f)
#define PLAYER1_HIGHLIGHT_COLOR glm::vec4(0.32f, 0.35f, 1.0f, 1.0f)

#define PLAYER2_NORMAL_COLOR glm::vec4(0.38f, 0.12f, 0.95f, 1.0f)
#define PLAYER2_HALFLIGHT_COLOR glm::vec4(0.95f, 0.13f, 0.95f, 1.0f)
#define PLAYER2_HIGHLIGHT_COLOR glm::vec4(0.58f, 0.37f, 1.0f, 1.0f)

class ApplicationControl;
class Game;

class Player
{
	ApplicationControl* appControl;
	Game* game;

	QString name;
	PlayerID id;
	int playerType;
	int aiType;
	std::set<Unit*> units;
	std::set<Unit*> deadUnits;

	glm::vec4 normalColor;
	glm::vec4 halflightColor;
	glm::vec4 highlightColor;

	int commandPoints = 0;

public:
	~Player();
	explicit Player(Game* inGame, PlayerID inID, QString inName, int inCode) : Player(nullptr, game, inID, inName, inCode){}
	explicit Player(ApplicationControl* inAppControl, Game* inGame, PlayerID inID, QString inName, int inCode);

	void DecodePlayerType(int code);

	void GamePopup(QString message) const;

	QString GetName() const
	{
		return name;
	}
	PlayerID GetID() const
	{
		return id;
	}

	Player* GetEnemyPlayer();
	std::vector<Player*> GetAllEnemyPlayers();

	std::set<Unit*> GetUnits() const
	{
		return units;
	}

	void AddNewUnit(Unit* newUnit);
	void AddNewUnitAndCreateUI(Unit* newUnit, Game* game, QQmlEngine* engine, QQuickItem* guiRoot);
	void OnUnitDeath(Unit* dyingUnit);

	void BeginTurn();
	void OnAbilityUsed();
	bool IsOutOfCommandPoints() const;
	void EndTurn();
};