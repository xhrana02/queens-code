//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include <memory>
#include <set>
#include "AiGameState.h"

class AiMove;

class AiBestMovesManager
{
public:
	std::set<std::shared_ptr<AiGameState>, AiGameStateComparator> bestMoves;
	int maxSize;

	explicit AiBestMovesManager(int inMaxSize);

	void AddNewMove(std::shared_ptr<AiGameState> newMove, bool counterMove = false);
	std::shared_ptr<AiGameState> GetBestMove();
	std::shared_ptr<AiGameState> GetWorstMove();
};
