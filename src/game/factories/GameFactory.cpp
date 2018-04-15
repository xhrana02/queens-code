//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "GameFactory.h"
#include "BoardFactory.h"

Game* GameFactory::CreateStandardGame(Player* player_1, Player* player_2, ModelLoader* modelLoader)
{
	modelLoader->LoadModel(APP_RESOURCES"/models/GrassyGround/GrassyGround.obj", "GrassyGround");
	modelLoader->LoadModel(APP_RESOURCES"/models/FieldBorder/FieldBorder.obj", "FieldBorder");

	auto newGame = new Game(player_1, player_2, BoardFactory::CreateStandardBoard());

	newGame->AddEnvironmentObject(new RenderingObject(modelLoader->GetModel("GrassyGround").get()));

	return newGame;
}
