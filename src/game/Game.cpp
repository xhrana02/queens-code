//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Game.h"
#include "Simple_geSGRenderer.h"
#include "../ApplicationControl.h"

using namespace fsg;
using namespace std;
using namespace glm;

/**
 * \brief Game constructor.
 * \param inBoard Game board.
 */
Game::Game(ApplicationControl* inAppControl, shared_ptr<Board> inBoard)
{
	appControl = inAppControl;
	gameBoard = inBoard;
	gameStage = Deploy;
}

void Game::StartGame() const
{
	player1->BeginTurn();
}

void Game::AddPlayer(std::shared_ptr<Player> newPlayer)
{
	if(newPlayer == nullptr)
	{
		throw exception("Game AddPlayer - New player was null.");
	}

	switch(newPlayer->GetID())
	{
	case Player1:
		player1 = newPlayer;
		break;
	case Player2:
		player2 = newPlayer;
		break;
	default:
		throw exception("Game AddPlayer - Invalid player ID.");
	}
}

Player* Game::GetNextPlayer() const
{
	if(activePlayer == nullptr)
	{
		throw exception("Game GetNextPlayer - Active player was null.");
	}

	switch(activePlayer->GetID())
	{
	case Player1:
		return player2.get();
	case Player2:
		return player1.get();
	default:
		throw exception("Game GetNextPlayer - Invalid player ID.");
	}
}

Player* Game::GetEnemyPlayer(Player* enemyOf) const
{
	if(enemyOf == nullptr)
	{
		throw exception("Game GetEnemyPlayer - Player parameter was null.");
	}

	switch(enemyOf->GetID())
	{
	case Player1:
		return player2.get();
	case Player2:
		return player1.get();
	default:
		throw exception("Game GetEnemyPlayer - Invalid player ID.");
	}
}

vector<Player*> Game::GetAllEnemyPlayers(Player* enemiesOf) const
{
	// IMPLEMENT THIS IF THERE ARE MORE THAN 2 PLAYERS IN THE GAME!!!
	return vector<Player*>({ GetEnemyPlayer(enemiesOf) });
}

void Game::PlayerDefeat(Player* defeatedPlayer)
{
	PlayerVictory(GetEnemyPlayer(defeatedPlayer));
}

void Game::PlayerVictory(Player* player)
{
	if(isRealGame)
	{
		UnselectUnit();
		locked = true;
		if(appControl != nullptr)
		{
			appControl->GamePopup(player->GetName() + " is victorious!");
		}
	}
	else
	{
		// TODO: Inform AI about player victory
	}
}

void Game::SetActivePlayer(Player* newActivePlayer)
{
	activePlayer = newActivePlayer;
	if(newActivePlayer->GetID() == Player1)
	{
		turnNumber++;
	}
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
	if (locked)
	{
		return;
	}

	auto newHoveredField = gameBoard->GetPlayFieldFromMouse(mouse);
	HoverField(newHoveredField);
}

/**
 * \param mouse Mouse position.
 * \param button Number of triggering mouse button.
 */
void Game::HandleMouseClick(vec2 mouse, MouseButton button)
{
	if (locked)
	{
		return;
	}

	auto clickedField = gameBoard->GetPlayFieldFromMouse(mouse);
	if (button == LMB)
	{
		SelectField(clickedField);
	}

	if (button == RMB)
	{
		UseAbility(clickedField);
	}
}

void Game::HoverField(Field* newHoveredField)
{
	if (newHoveredField != hoveredField)
	{
		hoveredField = newHoveredField;
		if (newHoveredField != nullptr)
		{
			gameBoard->HighlightField(newHoveredField);
		}
		else
		{
			gameBoard->UnhighlightAllFields();
		}
	}
}

void Game::SelectField(Field* clickedField)
{
	Unit* newSelectedUnit = nullptr;
	if (clickedField != nullptr)
	{
		newSelectedUnit = clickedField->GetUnitOnField();
	}

	if (newSelectedUnit != selectedUnit)
	{
		SelectUnit(newSelectedUnit);
	}
}

void Game::SelectUnit(Unit* newSelectedUnit)
{
	if (locked)
	{
		selectUnitAfterUnlock = newSelectedUnit;
		return;
	}

	UnselectUnit();

	selectedUnit = newSelectedUnit;

	if (newSelectedUnit != nullptr)
	{
		auto isEnemy = newSelectedUnit->GetOwner() != activePlayer;
		newSelectedUnit->Select(isEnemy);
		appControl->GetCameraControl()->PanToPosition(
			newSelectedUnit->GetRenderingPosX(), newSelectedUnit->GetRenderingPosZ());
	}
}

void Game::UnselectUnit()
{
	if (selectedUnit != nullptr)
	{
		selectedUnit->Unselect();
		selectedUnit = nullptr;
		gameBoard->UnhalflightAllFields();
	}
}

void Game::UseAbility(Field* clickedField)
{
	if (selectedUnit == nullptr)
	{
		return;
	}

	if (selectedUnit->GetOwner() != activePlayer)
	{
		return;
	}

	if (selectedUnit->UseSelectedAbility(clickedField))
	{
		if (isRealGame)
		{
			gameBoard->UnhalflightAllFields();
		}

		activePlayer->OnAbilityUsed();
		if (activePlayer->IsOutOfCommandPoints())
		{
			EndTurn();
		}
	}
}

void Game::SelectAbility(int slot) const
{
	if (locked)
	{
		return;
	}

	if (selectedUnit != nullptr)
	{
		selectedUnit->SelectAbility(slot);
	}
}

void Game::OnAbilitySelected(int slot) const
{
	if (locked)
	{
		return;
	}

	if (selectedUnit != nullptr)
	{
		selectedUnit->OnAbilitySelected(slot);
	}
}

void Game::EndTurn()
{
	if (locked)
	{
		endTurnAfterUnlock = true;
		return;
	}

	GetActivePlayer()->EndTurn();
}

void Game::LockGame(Ability* lockingAbility)
{
	if(isRealGame)
	{
		locked = true;
		lockingAbilities.push_back(lockingAbility);
	}
}

void Game::UnlockGame()
{
	locked = false;

	if(selectUnitAfterUnlock)
	{
		SelectUnit(selectUnitAfterUnlock);
		selectUnitAfterUnlock = nullptr;
	}
	else
	{
		selectedUnit->SelectAbility(1);
	}

	if(endTurnAfterUnlock)
	{
		EndTurn();
		endTurnAfterUnlock = false;
	}
}

void Game::LockedIteration()
{
	for (auto iterator = lockingAbilities.begin(); iterator != lockingAbilities.end();)
	{
		auto ability = *iterator;

		auto finished = ability->LockedIteration();
		if (finished)
		{
			lockingAbilities.erase(iterator);
			if(lockingAbilities.empty())
			{
				UnlockGame();
				break;
			}
		}
		else
		{
			++iterator;
		}
	}
}

void Game::IterationEvents()
{
	if(locked)
	{
		LockedIteration();
	}
}
