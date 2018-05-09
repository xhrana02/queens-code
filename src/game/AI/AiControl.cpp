//----------------------------------------------//
//  Author: Pavel Hranáč (xhrana02)             //
//  School: Vysoké učení technické v Brně       //
//  Faculty: Fakulta informačních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "AiControl.h"
#include "AiGame.h"
#include "AiMove.h"
#include "AiGameState.h"
#include "AiGameStateEvaluator.h"
#include "AiBestMovesManager.h"


AiControl::AiControl(AiType type, PlayerID inAiPlayerID)
{
	aiType = type;
	aiPlayerID = inAiPlayerID;
	evaluator = std::make_unique<AiGameStateEvaluator>(type, aiPlayerID);
}

std::list<std::shared_ptr<AiMove>> AiControl::GetNextMoves(Game* originGame)
{
	auto originState = std::make_unique<AiGameState>(originGame, aiType);

	// GENERATION 1
	auto gen1 = std::make_unique<AiBestMovesManager>(evaluator->config->gen1MaxMoves);
	processGeneration(gen1.get(), originState.get());

	// GENERATION 2
	auto gen1BestMoves = gen1->bestMoves;
	gen1.reset();
	gen1 = std::make_unique<AiBestMovesManager>(evaluator->config->gen1MaxMoves);
	for (auto gen1State : gen1BestMoves)
	{
		if (gen1State->moves.back()->type == EndTurnMove)
		{
			gen1->AddNewMove(gen1State);
			continue;
		}

		auto gen2 = std::make_unique<AiBestMovesManager>(evaluator->config->gen2MaxMoves);
		processGeneration(gen2.get(), gen1State.get());

		// GENERATION 3
		auto gen2BestMoves = gen2->bestMoves;
		gen2.reset();
		gen2 = std::make_unique<AiBestMovesManager>(1);
		for (auto gen2State : gen2BestMoves)
		{
			if (gen2State->moves.back()->type == EndTurnMove)
			{
				gen2->AddNewMove(gen2State);
				continue;
			}

			auto gen3 = std::make_unique<AiBestMovesManager>(1);
			processGeneration(gen3.get(), gen2State.get());

			gen2->AddNewMove(gen3->GetBestMove());
		}

		gen1->AddNewMove(gen2->GetBestMove());
	}

	auto bestFinalStates = gen1->bestMoves;
	gen1.reset();
	gen1 = std::make_unique<AiBestMovesManager>(1);
	for (auto state :  bestFinalStates)
	{
		auto genCounter = std::make_unique<AiBestMovesManager>(1);
		auto enemyID = Player1;
		if (aiPlayerID == Player1) { enemyID = Player2; }
		auto counterMoves = state->game->GetAllPlayerMoves(enemyID);
		for (auto move : counterMoves)
		{
			auto newGameState = state->MakeCopy();
			if (newGameState->AddMove(move))
			{
				newGameState->Evaluate(evaluator.get());
				// true setting makes the manager store the worst moves instead of the best ones
				genCounter->AddNewMove(newGameState, true);
			}
		}

		gen1->AddNewMove(genCounter->GetWorstMove());
	}

	auto bestMoveSequence = gen1->GetBestMove()->moves;
	bestMoveSequence.erase(std::prev(bestMoveSequence.end()));
	auto aiMovesList = std::list<std::shared_ptr<AiMove>>();
	std::copy( bestMoveSequence.begin(), bestMoveSequence.end(), back_inserter(aiMovesList));
	return aiMovesList;
}


void AiControl::processGeneration(AiBestMovesManager* genManager, AiGameState* sourceState)
{
	auto allMoves = sourceState->game->GetAllPlayerMoves(aiPlayerID);
	for (auto move : allMoves)
	{
		auto newGameState = sourceState->MakeCopy();
		if (newGameState->AddMove(move))
		{
			newGameState->Evaluate(evaluator.get());
			genManager->AddNewMove(newGameState);
		}
	}
}
