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
	player1 = shared_ptr<Player>(player_1);
	player2 = shared_ptr<Player>(player_2);
	gameBoard = shared_ptr<Board>(board);
	gameStage = Deploy;
}

void Game::AddEnvironmentObject(shared_ptr<RenderingObject> newObject)
{
	environmentObjects.push_back(newObject);
}

vector<RenderingObject*> Game::GetObjectsForRendering() const
{
	auto objects = vector<RenderingObject*>();

	for (auto envObject : environmentObjects)
	{
		objects.push_back(envObject.get());
	}

	auto fields = gameBoard->GetAllFields();
	for (auto field : fields)
	{
		for (auto fieldObject : field->GetRenderingObjects())
		{
			objects.push_back(fieldObject);
		}
	}

	return objects;
}

void Game::HandleMouseMovement(vec2 mouse) const
{
	auto hoveredField = gameBoard->GetPlayFieldFromMouse(mouse);
	if(hoveredField != nullptr)
	{
		gameBoard->HighlightField(hoveredField);
	}
	else
	{
		gameBoard->UnhighlightAllFields();
	}
}
