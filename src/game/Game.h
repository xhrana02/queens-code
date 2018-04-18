//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Player.h"
#include "Board.h"
#include "RenderingObject.h"
#include <glm/detail/type_vec2.hpp>

using namespace fsg;

enum GameStage { Deploy, Battle, GameOver };

class Game
{
	shared_ptr<Player> player1;
	shared_ptr<Player> player2;
	GameStage gameStage;
	shared_ptr<Board> gameBoard;

	vector<shared_ptr<RenderingObject>> environmentObjects;

public:
	Game(Player* player_1, Player* player_2, Board* board);

	Player* GetPlayer1() const
	{
		return player1.get();
	}

	Player* GetPlayer2() const
	{
		return player2.get();
	}

	Board* GetGameBoard() const
	{
		return gameBoard.get();
	}

	int GetMapSize() const
	{
		if(gameBoard->PlayableHeight() > gameBoard->PlayableWidth())
		{
			return gameBoard->PlayableHeight();
		}
		return gameBoard->PlayableWidth();
	}

	void AddEnvironmentObject(shared_ptr<RenderingObject> newObject);

	vector<RenderingObject*> GetObjectsForRendering() const;

	void HandleMouseMovement(vec2 mouse) const;
};
