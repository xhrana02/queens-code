//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "GameEnums.h"
#include "Player.h"
#include "Board.h"
#include "RenderingObject.h"
#include <glm/glm.hpp>

class AbilityAnimation;
class Cursor;

namespace fsg {
	class Simple_geSGRenderer;
}

class ApplicationControl;

class Game
{
	ApplicationControl* appControl;
	bool isRealGame = false;

	std::shared_ptr<Player> player1;
	std::shared_ptr<Player> player2;
	Player* activePlayer = nullptr;
	int turnNumber = 0;
	std::shared_ptr<Board> gameBoard;

	std::shared_ptr<Cursor> cursor;
	std::vector<std::shared_ptr<fsg::RenderingObject>> environmentObjects;
	glm::vec2 cursorPosition = glm::vec2(0.f, 0.f);
	float highlightFluctuationPhase = 0.0f;
	float highlightFluctuation = 0.0f;

	Field* hoveredField = nullptr;
	Unit* selectedUnit = nullptr;

	bool locked = false;
	std::vector<AbilityAnimation*> lockingAnimations;
	Unit* selectUnitAfterUnlock = nullptr;
	bool endTurnAfterUnlock = false;

public:
	~Game();
	explicit Game() : Game(nullptr) {}
	explicit Game(ApplicationControl* inAppControl);

	void ThisIsRealGame()
	{
		isRealGame = true;
	}
	bool IsRealGame() const
	{
		return isRealGame;
	}

	void StartGame() const;

	void AddPlayer(std::shared_ptr<Player> newPlayer);

	Player* GetPlayer1() const
	{
		return player1.get();
	}
	Player* GetPlayer2() const
	{
		return player2.get();
	}
	Player* GetNextPlayer() const;
	Player* GetEnemyPlayer(Player* enemyOf) const;
	std::vector<Player*> GetAllEnemyPlayers(Player* enemiesOf) const;

	void PlayerDefeat(Player* defeatedPlayer);
	void PlayerVictory(Player* victoriousPlayer);

	void SetActivePlayer(Player* newActivePlayer);
	Player* GetActivePlayer() const
	{
		return activePlayer;
	}

	int GetTurnNumber() const
	{
		return turnNumber;
	}

	void SetGameBoard(std::shared_ptr<Board> newBoard)
	{
		gameBoard = newBoard;
	}
	Board* GetGameBoard() const
	{
		return gameBoard.get();
	}
	int GetMapSize() const;

	void AddCursor(std::shared_ptr<Cursor> newCursor);
	void AddEnvironmentObject(std::shared_ptr<fsg::RenderingObject> newObject);

	void GetObjectsForRendering(fsg::Simple_geSGRenderer* renderer) const;
	void PanCameraToField(Field* centerField) const;
	void PanCameraToPosition(float posX, float posZ) const;

	void HandleMouseMovement(glm::vec2 mouse);
	void HandleMouseClick(glm::vec2 mouse, MouseButton button);
	void HoverField(Field* newHoveredField);
	void SelectField(Field* clickedField);
	void SelectUnit(Unit* newSelectedUnit);
	void UnselectUnit();
	void UseAbility(Field* clickedField);
	void SelectAbility(int slot) const;
	void OnAbilitySelected(int slot) const;
	void EndTurn();

	void LockGame(AbilityAnimation* lockingAnimation);
	void UnlockGame();
	void LockedIteration();

	void IterationEvents();
	void ResetTheoryValues() const;
};
