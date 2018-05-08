//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "AiBestMovesManager.h"


AiBestMovesManager::AiBestMovesManager(int inMaxSize)
{
	maxSize = inMaxSize;
	bestMoves = std::set<std::shared_ptr<AiGameState>, AiGameStateComparator>();
}

void AiBestMovesManager::AddNewMove(std::shared_ptr<AiGameState> newMove)
{
	for (auto move : bestMoves)
	{
		if (newMove->evaluation == move->evaluation)
		{
			// don't accept duplicit moves
			return;
		}
	}

	if (bestMoves.size() < maxSize )
	{
		bestMoves.insert(newMove);
	}
	else
	{
		if (newMove->evaluation > (*bestMoves.begin())->evaluation)
		{
			bestMoves.erase(bestMoves.begin());
			bestMoves.insert(newMove);
		}
	}
}

std::shared_ptr<AiGameState> AiBestMovesManager::GetBestMove()
{
	if (bestMoves.size() < 1)
	{
		throw std::exception("AiBestMovesManager::GetBestMove - Best moves container was empty.");
	}

	return *bestMoves.rbegin();
}
