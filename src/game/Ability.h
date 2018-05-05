//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include <QString>

class Field;
class Unit;
class Board;
class Game;

class Ability
{
protected:
	QString name;
	QString iconPath;
	QString description;
	bool isPassive = false;
	int costEN = 0;
	int costHP = 0;

	Game* game = nullptr;
public:
	virtual ~Ability() = default;
	virtual bool Effect(Board* board, Unit* abilityUser, Field* target) = 0;
	virtual bool CanUse(Board* board, Unit* abilityUser, Field* target) = 0;
	virtual void OnSelected(Board* board, Unit* abilityUser) = 0;
	virtual void SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField);

	bool CanAfford(Unit* abilityUser) const;
	void PanCameraToTarget(Field* target) const;

	QString GetName() const
	{
		return name;
	}

	QString GetIconPath() const
	{
		return iconPath;
	}

	QString GetDescription() const
	{
		return description;
	}

	bool IsPassive() const
	{
		return isPassive;
	}

	void SetGame(Game* activeGame)
	{
		game = activeGame;
	}

};
