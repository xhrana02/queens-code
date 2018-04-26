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
#include <glm/glm.hpp>

namespace fsg {
	class Simple_geSGRenderer;
}

enum GameStage { Deploy, Battle, GameOver };
enum MouseButton { LMB, RMB, MMB };

class Game
{
	std::shared_ptr<Player> player1;
	std::shared_ptr<Player> player2;
	GameStage gameStage;
	std::shared_ptr<Board> gameBoard;

	std::vector<std::shared_ptr<fsg::RenderingObject>> environmentObjects;

	Field* hoveredField = nullptr;
	Unit* selectedUnit = nullptr;

	bool locked = false;
	std::vector<Ability*> lockingAbilities;

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

	int GetMapSize() const;

	void AddEnvironmentObject(std::shared_ptr<fsg::RenderingObject> newObject);

	void GetObjectsForRendering(fsg::Simple_geSGRenderer* renderer) const;

	void HandleMouseMovement(glm::vec2 mouse);
	void HandleMouseClick(glm::vec2 mouse, MouseButton button);

	void LockGame(Ability* lockingAbility);
	void LockingIteration();
};
