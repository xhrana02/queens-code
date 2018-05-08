//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "AiGame.h"
#include "AiBoard.h"
#include "AiMoveEndTurn.h"


AiGame::AiGame(Game* source, AiType aiType)
{
	AddPlayer(CopyPlayer(source->GetPlayer1(), this, aiType));
	AddPlayer(CopyPlayer(source->GetPlayer2(), this, aiType));
	SetActivePlayer(source->GetActivePlayer());
	SetGameBoard( std::make_shared<AiBoard>(source->GetGameBoard(), this) );
}

std::shared_ptr<Player> AiGame::CopyPlayer(Player* source, AiGame* newGame, AiType aiType)
{
	auto newPlayer = std::make_shared<Player>(newGame, source->GetID(), aiType);
	newPlayer->SetCommandPoints(source->GetCommandPoints());
	return newPlayer;
}

void AiGame::PlayerVictory(Player* victoriousPlayer)
{
	finished = true;
	wonBy = victoriousPlayer->GetID();
}

std::vector<std::shared_ptr<AiMove>> AiGame::GetAllPlayerMoves(PlayerID playerID) const
{
	auto moves = std::vector<std::shared_ptr<AiMove>>();
	for (auto unit : GetPlayerByID(playerID)->GetUnits())
	{
		for (auto move : unit->GetAllPossibleMoves())
		{
			moves.push_back(move);
		}
	}
	moves.push_back(std::make_shared<AiMoveEndTurn>(playerID));
	return moves;
}
