//----------------------------------------------//
//  Author: Pavel Hranáč (xhrana02)             //
//  School: Vysoké učení technické v Brně       //
//  Faculty: Fakulta informačních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "GameEnums.h"
#include "AiConfiguration.h"
#include <memory>

class Board;
class Player;
class AiGame;
class Field;
class Unit;
class AiConfiguration;

class AiGameStateEvaluator
{
public:
	std::unique_ptr<AiConfiguration> config;
	PlayerID evalPlayerID;
	Field* playerUnitsCenter = nullptr;
	float snowballFactor = 0.0f;

	explicit AiGameStateEvaluator(AiType type, PlayerID inEvalPlayerID);
	long EvaluateGameState(AiGame* game);
	long EvaluateUnitStaticValue(Unit* unit) const;
	long EvaluateUnitActiveValue(Unit* unit) const;
	static int GetDistanceFactor(Field* from, Field* to);
	static int GetYDeltaFactor(Field* from, Field* to);
	void CalculateUnitsCenter(Player* player, Board* board);
	void CalculateSnowballFactor(Player* evalPlayer, Player* enemyPlayer);
	static void ResetDangerFactors(Player* evalPlayer, Player* enemyPlayer);
	static float GetUnitToughness(Unit* unit);
};
