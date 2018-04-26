//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Game.h"
#include "Simple_geSGRenderer.h"

using namespace fsg;
using namespace std;
using namespace glm;

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

int Game::GetMapSize() const
{
	if(gameBoard->PlayableHeight() > gameBoard->PlayableWidth())
	{
		return gameBoard->PlayableHeight();
	}
	return gameBoard->PlayableWidth();
}

////////////////////////////////////////////////////////////////////////////////
// RENDERING


void Game::AddEnvironmentObject(shared_ptr<RenderingObject> newObject)
{
	environmentObjects.push_back(newObject);
}

void Game::GetObjectsForRendering(Simple_geSGRenderer* renderer) const
{
	// RENDERING OBJECTS
	auto objects = vector<RenderingObject*>();

	for (auto envObject : environmentObjects)
	{
		objects.push_back(envObject.get());
	}

	for (auto field : gameBoard->GetAllFields())
	{
		for (auto fieldObject : field->GetRenderingObjects())
		{
			objects.push_back(fieldObject);
		}
	}

	renderer->SetObjects(objects);

	// INFO BARS (HEALTH BAR, ENERGY BAR)
	for (auto unit : player1->GetUnits())
	{
		unit->UpdateInfoBar(renderer->GetPerspectiveMatrix(), renderer->GetViewMatrix(),
			renderer->GetWindowWidth(), renderer->GetWindowHeight());
	}
	for (auto unit : player2->GetUnits())
	{
		unit->UpdateInfoBar(renderer->GetPerspectiveMatrix(), renderer->GetViewMatrix(),
			renderer->GetWindowWidth(), renderer->GetWindowHeight());
	}

}

////////////////////////////////////////////////////////////////////////////////
// MOUSE EVENTS

void Game::HandleMouseMovement(vec2 mouse)
{
	if(locked)
	{
		return;
	}

	auto newHoveredField = gameBoard->GetPlayFieldFromMouse(mouse);
	if(newHoveredField != hoveredField)
	{
		if(newHoveredField != nullptr)
		{
			gameBoard->HighlightField(newHoveredField);
		}
		else
		{
			gameBoard->UnhighlightAllFields();
		}
	}
	hoveredField = newHoveredField;
}

/**
 * \param mouse Mouse position.
 * \param button Number of triggering mouse button.
 */
void Game::HandleMouseClick(vec2 mouse, MouseButton button)
{
	if(locked)
	{
		return;
	}

	auto clickedField = gameBoard->GetPlayFieldFromMouse(mouse);
	if(button == LMB)
	{
		Unit* newSelectedUnit = nullptr;
		if (clickedField != nullptr)
		{
			newSelectedUnit = clickedField->GetUnitOnField();
		}

		if (newSelectedUnit != selectedUnit)
		{
			if (selectedUnit != nullptr)
			{
				selectedUnit->Unselect();
			}

			if (newSelectedUnit != nullptr)
			{
				newSelectedUnit->Select();
			}
		}
		selectedUnit = newSelectedUnit;
	}
}

void Game::LockGame(Ability* lockingAbility)
{
	locked = true;
	lockingAbilities.push_back(lockingAbility);
}

void Game::LockingIteration()
{
	auto abilityIndex = 0;
	for (auto ability : lockingAbilities)
	{
		auto finished = ability->LockedIteration();
		if (finished)
		{
			lockingAbilities.erase(lockingAbilities.begin() + abilityIndex);
			if(lockingAbilities.empty())
			{
				locked = false;
			}
		}
		else
		{
			// finished abilities already reduce size
			abilityIndex++;
		}
	}
}
