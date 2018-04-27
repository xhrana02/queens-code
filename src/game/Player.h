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

#define PLAYER1_NORMAL_COLOR glm::vec4(0.75f, 0.17f, 0.17f, 1.0f)
#define PLAYER1_HALFLIGHT_COLOR glm::vec4(0.85f, 0.23f, 0.18f, 1.0f)
#define PLAYER1_HIGHLIGHT_COLOR glm::vec4(0.95f, 0.23f, 0.23f, 1.0f)

#define PLAYER2_NORMAL_COLOR glm::vec4(0.19f, 0.19f, 0.85f, 1.0f)
#define PLAYER2_HALFLIGHT_COLOR glm::vec4(0.27f, 0.20f, 0.9f, 1.0f)
#define PLAYER2_HIGHLIGHT_COLOR glm::vec4(0.27f, 0.27f, 0.95f, 1.0f)

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
	std::vector<Unit*> units;

	glm::vec4 normalColor;
	glm::vec4 halflightColor;
	glm::vec4 highlightColor;

	int commandPoints = 0;

public:
	~Player();
	explicit Player(Game* inGame, PlayerID inID, QString inName, int inCode) : Player(nullptr, game, inID, inName, inCode){}
	explicit Player(ApplicationControl* inAppControl, Game* inGame, PlayerID inID, QString inName, int inCode);

	QString GetName() const
	{
		return name;
	}
	PlayerID GetID() const
	{
		return id;
	}

	void DecodePlayerType(int code);

	std::vector<Unit*> GetUnits() const
	{
		return units;
	}
	void AddNewUnit(Unit* newUnit);
	void AddNewUnitAndCreateUI(Unit* newUnit, Game* game, QQmlEngine* engine, QQuickItem* guiRoot);

	void BeginTurn();
	void OnAbilityUsed();
	bool IsOutOfCommandPoints() const;
	void EndTurn();
};