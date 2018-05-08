//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "GameEnums.h"
#include <memory>
#include <vector>

class Game;
class AiMove;
class AiGame;
class AiGameStateEvaluator;

class AiGameState
{
public:
	std::vector<std::shared_ptr<AiMove>> moves = std::vector<std::shared_ptr<AiMove>>();
	std::shared_ptr<AiGame> game;
	AiType aiType;
	long evaluation = 0;

	explicit AiGameState(Game* oldGame, AiType inAiType);
	std::shared_ptr<AiGameState> MakeCopy();

	bool AddMove(std::shared_ptr<AiMove> inMove);
	void Evaluate(AiGameStateEvaluator* evaluator);
};

struct AiGameStateComparator
{
	bool operator() (const std::shared_ptr<AiGameState>& left, const std::shared_ptr<AiGameState>& right) const{
		return left->evaluation < right->evaluation;
	}
};