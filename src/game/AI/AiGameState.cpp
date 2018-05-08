//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "AiGameState.h"
#include "AiGame.h"
#include "AiMove.h"
#include "AiGameStateEvaluator.h"

AiGameState::AiGameState(Game* oldGame, AiType inAiType)
{
	aiType = inAiType;
	game = std::make_unique<AiGame>(oldGame, aiType);
}

std::shared_ptr<AiGameState> AiGameState::MakeCopy()
{
	auto copy = std::make_shared<AiGameState>(game.get(), aiType);
	copy->moves = moves;
	copy->evaluation = evaluation;
	return copy;
}

bool AiGameState::AddMove(std::shared_ptr<AiMove> inMove)
{
	for (auto move : moves)
	{
		if (move->abilitySlot == 1 && inMove->abilitySlot == 1 &&
			move->targetX == inMove->userX && move->targetY == inMove->userY)
		{
			// prevent double moves
			return false;
		}
	}

	if(inMove->UseThisMove(game.get()))
	{
		moves.push_back(inMove);
		return true;
	}
	return false;
}

void AiGameState::Evaluate(AiGameStateEvaluator* evaluator)
{
	evaluation = evaluator->EvaluateGameState(game.get());
}
