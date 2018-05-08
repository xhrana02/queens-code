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

class AiGame;
class Field;
class Unit;
class AiConfiguration;

class AiGameStateEvaluator
{
public:
	std::unique_ptr<AiConfiguration> config;
	PlayerID evalPlayerID;

	explicit AiGameStateEvaluator(AiType type, PlayerID inEvalPlayerID);
	long EvaluateGameState(AiGame* game) const;
	long EvaluateUnit(Unit* unit) const;
	long EvaluateUnitTargets(Unit* unit) const;
	static float GetDistance(Field* from, Field* to);
};
