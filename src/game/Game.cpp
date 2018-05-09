//----------------------------------------------//
//  Author: Pavel Hranáč (xhrana02)             //
//  School: Vysoké učení technické v Brně       //
//  Faculty: Fakulta informačních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Game.h"
#include "Simple_geSGRenderer.h"
#include "../ApplicationControl.h"
#include "Cursor.h"
#include "AbilityAnimation.h"

using namespace fsg;
using namespace std;
using namespace glm;

Game::~Game()
{
    for (auto animation : lockingAnimations)
    {
        delete animation;
    }
}

/**
 * \brief Game constructor.
 */
Game::Game(ApplicationControl* inAppControl)
{
    appControl = inAppControl;
}

void Game::StartGame() const
{
    player1->BeginTurn();
    if (IsRealGame())
    {
        PanCameraToField((*player1->GetUnits().begin())->GetOccupiedField());
    }
}

void Game::AddPlayer(shared_ptr<Player> newPlayer)
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

Player* Game::GetPlayerByID(PlayerID playerID) const
{
	switch (playerID)
	{
	case Player1:
		return player1.get();
	case Player2:
		return player2.get();
	default:
		throw exception("Game GetPlayerByID - Invalid player ID.");
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
        gameBoard->UnhighlightAllFields();
        gameBoard->UnhalflightAllFields();
        ResetTheoryValues();
        locked = true;
		finished = true;
        if(appControl != nullptr)
        {
            appControl->SetActivePlayer(player->GetName() + " is victorious!");
            appControl->OnGameOver();
        }
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

void Game::AddCursor(shared_ptr<Cursor> newCursor)
{
    cursor = newCursor;
}

void Game::AddEnvironmentObject(shared_ptr<RenderingObject> newObject)
{
    environmentObjects.push_back(newObject);
}

void Game::GetObjectsForRendering(Simple_geSGRenderer* renderer) const
{
    // RENDERING OBJECTS
    auto objects = vector<RenderingObject*>();

    if (cursor.get() != nullptr)
    {
        objects.push_back(cursor->GetRenderingObject());
    }

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
            renderer->GetWindowWidth(), renderer->GetWindowHeight(), highlightFluctuation);
    }
    for (auto unit : player2->GetUnits())
    {
        unit->UpdateInfoBar(renderer->GetPerspectiveMatrix(), renderer->GetViewMatrix(),
            renderer->GetWindowWidth(), renderer->GetWindowHeight(), highlightFluctuation);
    }

}

void Game::PanCameraToField(Field* centerField) const
{
    PanCameraToPosition(centerField->GetRenderingPosX(), centerField->GetRenderingPosZ());
}

void Game::PanCameraToPosition(float posX, float posZ) const
{
    appControl->GetCameraControl()->PanToPosition(posX, posZ);
}

////////////////////////////////////////////////////////////////////////////////
// MOUSE EVENTS

void Game::HandleMouseMovement(vec2 mouse)
{
    auto newHoveredField = gameBoard->GetPlayFieldFromMouse(mouse);
    if (newHoveredField != nullptr)
    {
        cursorPosition = vec2(newHoveredField->GetRenderingPosX(), newHoveredField->GetRenderingPosZ());
    }
    else
    {
        cursorPosition = mouse;
    }

    if (locked)
    {
        return;
    }

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
	if (activePlayer->IsAI())
	{
		return;
	}

    if (newHoveredField != hoveredField)
    {
        ResetTheoryValues();

        hoveredField = newHoveredField;
        if (newHoveredField != nullptr)
        {
            if (selectedUnit == nullptr)
            {
                gameBoard->HighlightField(newHoveredField);
            }
            else
            {
                selectedUnit->SelectedUnitOnFieldHovered(newHoveredField);
            }
        }
        else
        {
            gameBoard->UnhighlightAllFields();
        }
    }
}

void Game::SelectField(Field* clickedField)
{
	if (activePlayer->IsAI())
	{
		return;
	}

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
	if (activePlayer->IsAI())
	{
		return;
	}

    if (locked)
    {
        selectUnitAfterUnlock = newSelectedUnit;
        return;
    }

    UnselectUnit();

    selectedUnit = newSelectedUnit;

    if (newSelectedUnit != nullptr)
    {
        newSelectedUnit->Select();
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

void Game::UseAbility(Field* clickedField) const
{
	if (activePlayer->IsAI())
	{
		return;
	}

    if (selectedUnit == nullptr)
    {
        return;
    }

    if (selectedUnit->GetOwnerID() != activePlayer->GetID())
    {
        return;
    }

    if (selectedUnit->UseSelectedAbility(clickedField))
    {
        if (isRealGame)
        {
            gameBoard->UnhalflightAllFields();
            ResetTheoryValues();
        }
    }
}

void Game::SelectAbility(int slot) const
{
	if (activePlayer->IsAI())
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
    if (selectedUnit != nullptr)
    {
		auto isEnemy = selectedUnit->GetOwnerID() != activePlayer->GetID();
        selectedUnit->OnAbilitySelected(slot, isEnemy);
        if (hoveredField != nullptr)
        {
            ResetTheoryValues();
            selectedUnit->SelectedUnitOnFieldHovered(hoveredField);
        }
    }
}

void Game::OnTurnEnd()
{
    if (locked)
    {
        endTurnAfterUnlock = true;
        return;
    }

	GetNextPlayer()->BeginTurn();
}

void Game::LockGame(AbilityAnimation* lockingAbility)
{
    if(isRealGame)
    {
        locked = true;
        lockingAnimations.push_back(lockingAbility);
    }
}

void Game::UnlockGame()
{
	if (finished)
	{
		return;
	}

    locked = false;

    if(selectUnitAfterUnlock)
    {
        SelectUnit(selectUnitAfterUnlock);
        selectUnitAfterUnlock = nullptr;
    }
    else if(selectedUnit)
    {
		selectedUnit->SelectAbility(1);
    }

    if(endTurnAfterUnlock)
    {
		endTurnAfterUnlock = false;
        OnTurnEnd();
    }
}

void Game::LockedIteration()
{
    for (auto iterator = lockingAnimations.begin(); iterator != lockingAnimations.end();)
    {
        auto animation = *iterator;

        auto finished = animation->Iteration();
        if (finished)
        {
            iterator = lockingAnimations.erase(iterator);
            if(lockingAnimations.empty())
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

    highlightFluctuationPhase += 1.5f; // 1 second from normal to fully highlighted
    if (highlightFluctuationPhase > 180.f)
    {
        // only positive sin values
        highlightFluctuationPhase -= 180.f;
    }
    highlightFluctuation = sin(radians(highlightFluctuationPhase));

    for (auto hlField : gameBoard->GetAllHighlightedFields())
    {
        for (auto hlObject : hlField->GetRenderingObjects())
        {
            hlObject->Fluctuate(highlightFluctuation);
        }
    }

    if (cursor.get() != nullptr)
    {
        cursor->Update(cursorPosition.x, cursorPosition.y, highlightFluctuationPhase);
    }

	if (activePlayer->IsAI())
	{
		ProcessAiTurn();
	}
}

void Game::ResetTheoryValues() const
{
    for (auto unit : player1->GetUnits())
    {
        unit->ResetTheory();
    }
    for (auto unit : player2->GetUnits())
    {
        unit->ResetTheory();
    }
}

void Game::ProcessAiTurn()
{
	// Give the human player a second or two to realize what happenned
	if (aiMoveLockoutDuration > 0)
	{
		aiMoveLockoutDuration--;
		return;
	}

	// Ask for new moves
	if (aiMoves.empty() && !aiThinking)
	{
		isRealGame = false;
		aiThinking = true;
		if (appControl)
		{
			appControl->IsAiThinking(true);
		}

		aiMovesFuture = async(launch::async, &Player::GetAiMoves, activePlayer);
	}

	// Check if new moves are ready
	if (aiThinking)
	{
		if (aiMovesFuture.wait_for(chrono::seconds(0)) == future_status::ready)
		{
			isRealGame = true;
			aiThinking = false;
			if (appControl)
			{
				appControl->IsAiThinking(false);
			}

			aiMoves = aiMovesFuture.get();
		}
	}

	// Apply the new moves
	if (!aiMoves.empty() && !locked)
	{
		if(aiMoves.front()->UseThisMove(this))
		{
			aiMoveLockoutDuration = 120;
			aiMoves.pop_front();
		}
		else
		{
			// AI move was invalid
			activePlayer->EndTurn();
		}
	}
}
