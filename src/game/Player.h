//----------------------------------------------//
//  Author: Pavel Hranáč (xhrana02)             //
//  School: Vysoké učení technické v Brně       //
//  Faculty: Fakulta informačních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "GameEnums.h"
#include "Unit.h"
#include <QObject>
#include "AiControl.h"
#include <unordered_set>

#define PLAYER1_NORMAL_COLOR glm::vec4(0.19f, 0.21f, 0.85f, 1.0f)
#define PLAYER1_HALFLIGHT_COLOR glm::vec4(0.21f, 0.85f, 0.85f, 1.0f)
#define PLAYER1_HIGHLIGHT_COLOR glm::vec4(0.32f, 0.35f, 1.0f, 1.0f)

#define PLAYER2_NORMAL_COLOR glm::vec4(0.38f, 0.12f, 0.95f, 1.0f)
#define PLAYER2_HALFLIGHT_COLOR glm::vec4(0.95f, 0.13f, 0.95f, 1.0f)
#define PLAYER2_HIGHLIGHT_COLOR glm::vec4(0.58f, 0.37f, 1.0f, 1.0f)

#define NEUTRAL_NORMAL_COLOR glm::vec4(0.88f, 0.88f, 0.88f, 1.0f)
#define NEUTRAL_HALFLIGHT_COLOR glm::vec4(0.94f, 0.94f, 0.94f, 1.0f)
#define NEUTRAl_HIGHLIGHT_COLOR glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)

class ApplicationControl;
class Game;

class Player
{
protected:
    ApplicationControl* appControl;
    Game* game;

    QString name;
    PlayerID id;
    AiType aiType;
	std::unique_ptr<AiControl> aiControl;

    std::unordered_set<Unit*> units = std::unordered_set<Unit*>();
    std::unordered_set<Unit*> deadUnits = std::unordered_set<Unit*>();

    glm::vec4 normalColor;
    glm::vec4 halflightColor;
    glm::vec4 highlightColor;

    int commandPoints = 0;

public:
    virtual ~Player();
	Player(Game* inGame, PlayerID inID, AiType inAiType) : Player(inGame, inID, "", inAiType) {}
    Player(Game* inGame, PlayerID inID, QString inName, AiType inAiType) : Player(nullptr, inGame, inID, inName, inAiType) {}
    Player(ApplicationControl* inAppControl, Game* inGame, PlayerID inID, QString inName, AiType inAiType);

    static AiType DecodeAiType(int code);

    void GamePopup(QString message) const;

    QString GetName() const
    {
        return name;
    }
    PlayerID GetID() const
    {
        return id;
    }
	AiType GetAiType() const
    {
		return aiType;
    }
	bool IsAI() const;

    Player* GetEnemyPlayer();
    std::vector<Player*> GetAllEnemyPlayers();

    std::unordered_set<Unit*> GetUnits() const
    {
        return units;
    }

    void AddNewUnit(Unit* newUnit);
    void AddNewUnitAndCreateUI(Unit* newUnit, QQmlEngine* engine, QQuickItem* guiRoot);
    void OnUnitDeath(Unit* dyingUnit);

    void BeginTurn();
    void OnAbilityUsed();
    bool IsOutOfCommandPoints() const;
    void EndTurn();

	int GetCommandPoints() const
	{
		return commandPoints;
	}
	void SetCommandPoints(int newValue)
	{
		commandPoints = newValue;
	}

	std::list<std::shared_ptr<AiMove>> GetAiMoves() const;
};