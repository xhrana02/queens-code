//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Game.h"
#include "ModelLoader.h"

class GameFactory
{
public:
	static Game* CreateStandardGame(Player* player_1, Player* player_2, fsg::ModelLoader* modelLoader);
};
