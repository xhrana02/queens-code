//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "GameEnums.h"
#include "AiGameStateEvaluator.h"
#include "AiMove.h"
#include <memory>
#include <list>

class AiGameState;
class AiBestMovesManager;
class Player;

class AiControl
{
	std::unique_ptr<AiGameStateEvaluator> evaluator;
	AiType aiType;
	PlayerID aiPlayerID;
public:
	explicit AiControl(AiType type, PlayerID inAiPlayerID);

	std::list<std::shared_ptr<AiMove>> GetNextMoves(Game* originGame);
private:
	void processGeneration(AiBestMovesManager* genManager, AiGameState* sourceState);
};
