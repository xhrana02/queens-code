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

using namespace fsg;

enum GameStage { Deploy, Battle, GameOver };

class Game
{
	Player* player1;
	Player* player2;
	GameStage gameStage;
	Board* gameBoard;

	vector<shared_ptr<RenderingObject>> environmentObjects;

public:
	Game(Player* player_1, Player* player_2, Board* board);

	Player* GetPlayer1() const
	{
		return player1;
	}

	Player* GetPlayer2() const
	{
		return player2;
	}

	Board* GetGameBoard() const
	{
		return gameBoard;
	}

	int GetMapSize() const
	{
		if(gameBoard->PlayableHeight() > gameBoard->PlayableWidth())
		{
			return gameBoard->PlayableHeight();
		}
		return gameBoard->PlayableWidth();
	}

	void AddEnvironmentObject(RenderingObject* newObject);

	vector<RenderingObject*> GetObjectsForRendering() const;
};
