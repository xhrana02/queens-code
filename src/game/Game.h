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

enum GameStage { Deploy, Battle, GameOver };

class Game
{
	std::shared_ptr<Player> player1;
	std::shared_ptr<Player> player2;
	GameStage gameStage;
	std::shared_ptr<Board> gameBoard;

	std::vector<std::shared_ptr<fsg::RenderingObject>> environmentObjects;

	Field* hoveredField = nullptr;

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

	void AddEnvironmentObject(std::shared_ptr<fsg::RenderingObject> newObject);

	std::vector<fsg::RenderingObject*> GetObjectsForRendering() const;

	void HandleMouseMovement(glm::vec2 mouse) const;
};
