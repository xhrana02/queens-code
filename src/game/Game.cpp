//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Game.h"

/**
 * \brief Game constructor.
 * \param player_1 First player.
 * \param player_2 Second player.
 * \param board Game board.
 */
Game::Game(Player* player_1, Player* player_2, Board* board)
{
	player1 = player_1;
	player2 = player_2;
	gameBoard = board;
	gameStage = Deploy;
}

void Game::AddEnvironmentObject(RenderingObject* newObject)
{
	environmentObjects.push_back(shared_ptr<RenderingObject>(newObject));
}

vector<RenderingObject*> Game::GetObjectsForRendering() const
{
	auto objects = vector<RenderingObject*>();
	auto fields = gameBoard->GetAllFields();

	for (auto envObject : environmentObjects)
	{
		objects.push_back(envObject.get());
	}

	return objects;
}
