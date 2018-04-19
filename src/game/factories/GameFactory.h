//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
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
