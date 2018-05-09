//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include <QString>
#include <vector>

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
	std::vector<Field*> viableTargets = std::vector<Field*>();
	virtual void calculateViableTargets(Board* board, Unit* abilityUser) = 0;

	Game* game = nullptr;

	int aiTargetValue = 0;
	bool aiCanHurt = false;
	float aiTargetMissingHpMod = 0.0f;
	float aiTargetMissingEnMod = 0.0f;
	float aiTargetRelativeEnMod = 0.0f;

public:
	virtual ~Ability() = default;
	virtual bool Effect(Board* board, Unit* abilityUser, Field* target) = 0;
	virtual bool CanAfford(Unit* abilityUser) const;
	virtual bool CanUse(Board* board, Unit* abilityUser, Field* target);
	virtual void OnSelected(Board* board, Unit* abilityUser) = 0;
	virtual void SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField);
	void CalculateViableTargets(Board* board, Unit* abilityUser);

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

	int GetCostEN() const
	{
		return costEN;
	}

	int GetCostHP() const
	{
		return costHP;
	}

	std::vector<Field*> GetViableTargets() const
	{
		return viableTargets;
	}

	int GetAiTargetValue() const
	{
		return aiTargetValue;
	}
	bool GetAiCanHurt() const
	{
		return aiCanHurt;
	}
	float GetAiTargetMissingHpMod() const
	{
		return aiTargetMissingHpMod;
	}
	float GetAiTargetMissingEnMod() const
	{
		return aiTargetMissingEnMod;
	}
	float GetAiTargetRelativeEnMod() const
	{
		return aiTargetRelativeEnMod;
	}
	virtual void SetAiCalculatedCost(int newCost)
	{
		// do nothing
	}

};
