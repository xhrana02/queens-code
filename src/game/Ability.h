//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include <string>

class Field;
class Unit;
class Board;

class Ability
{
protected:
	std::string description;
	std::string iconName;
	int costEN = 0;
	int costHP = 0;
public:
	virtual ~Ability() = default;
	virtual void Effect(Board* board, Unit* abilityUser, Field* target) = 0;
	virtual bool CanUse(Board* board, Unit* abilityUser, Field* target) = 0;
	bool CanAfford(Unit* abilityUser) const;
};
