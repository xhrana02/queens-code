//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include <QObject>
#include "Unit.h"

class Player
{
	QString _name;
	int _playerType;
	int _aiType;
	std::vector<Unit*> _units;

public:
	explicit Player(QString name, int code);

	QString GetName() const { return _name; }

	void DecodePlayerType(int code);
};

enum PlayerType {Human, AI};
enum AIType {None, Easy, Normal, Hard, Custom};