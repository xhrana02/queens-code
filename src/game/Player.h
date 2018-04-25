//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Unit.h"
#include <QObject>

class Player
{
	QString name;
	int playerType;
	int aiType;
	std::vector<Unit*> units;

public:
	~Player();
	explicit Player(QString inName, int inCode);

	QString GetName() const { return name; }

	void DecodePlayerType(int code);

	std::vector<Unit*> GetUnits() const
	{
		return units;
	}
	void AddNewUnit(Unit* newUnit)
	{
		units.push_back(newUnit);
	}

};

enum PlayerType {Human, AI};
enum AIType {None, Easy, Normal, Hard, Custom};