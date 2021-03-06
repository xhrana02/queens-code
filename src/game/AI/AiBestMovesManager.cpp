//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "AiBestMovesManager.h"


AiBestMovesManager::AiBestMovesManager(int inMaxSize)
{
	maxSize = inMaxSize;
	bestMoves = std::set<std::shared_ptr<AiGameState>, AiGameStateComparator>();
}

void AiBestMovesManager::AddNewMove(std::shared_ptr<AiGameState> newMove, bool counterMove)
{
	for (auto move : bestMoves)
	{
		if (newMove->evaluation == move->evaluation)
		{
			// don't accept duplicit game states
			return;
		}
	}

	if (bestMoves.size() < maxSize )
	{
		bestMoves.insert(newMove);
	}
	else
	{
		if (!counterMove)
		{
			if (newMove->evaluation > (*bestMoves.begin())->evaluation)
			{
				bestMoves.erase(bestMoves.begin());
				bestMoves.insert(newMove);
			}
		}
		else
		{
			if (newMove->evaluation < (*bestMoves.rbegin())->evaluation)
			{
				bestMoves.erase(prev(bestMoves.end()));
				bestMoves.insert(newMove);
			}
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

std::shared_ptr<AiGameState> AiBestMovesManager::GetWorstMove()
{
	if (bestMoves.size() < 1)
	{
		throw std::exception("AiBestMovesManager::GetWorstMove - Best moves container was empty.");
	}

	return *bestMoves.begin();
}
