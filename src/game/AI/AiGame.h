//----------------------------------------------//
//  Author: Pavel Hranáč (xhrana02)             //
//  School: Vysoké učení technické v Brně       //
//  Faculty: Fakulta informačních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Game.h"

class AiConfiguration;

class AiGame : public Game
{
public:
	PlayerID wonBy;

	explicit AiGame(Game* source, AiType aiType);

	static std::shared_ptr<Player> CopyPlayer(Player* source, AiGame* newGame, AiType aiType);
	void PlayerVictory(Player* victoriousPlayer) override;
	std::vector<std::shared_ptr<AiMove>> GetAllPlayerMoves(PlayerID playerID) const;
	bool IsFinished() const
	{
		return finished;
	}
	AiType GetAiType() const
	{
		return GetPlayer1()->GetAiType();
	}
};
