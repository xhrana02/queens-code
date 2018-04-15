//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "BoardFactory.h"

Board* BoardFactory::CreateStandardBoard()
{
	auto newBoard = new Board(15, 15);

	// bottom left corner
	newBoard->GetField(5, 5)->SetTerrainType(Wall);
	newBoard->GetField(5, 6)->SetTerrainType(Wall);
	newBoard->GetField(6, 5)->SetTerrainType(Wall);

	// top left corner
	newBoard->GetField(5, 11)->SetTerrainType(Wall);
	newBoard->GetField(5, 10)->SetTerrainType(Wall);
	newBoard->GetField(6, 11)->SetTerrainType(Wall);

	// bottom right corner
	newBoard->GetField(11, 5)->SetTerrainType(Wall);
	newBoard->GetField(10, 5)->SetTerrainType(Wall);
	newBoard->GetField(11, 6)->SetTerrainType(Wall);

	// top right corner
	newBoard->GetField(11, 11)->SetTerrainType(Wall);
	newBoard->GetField(10, 11)->SetTerrainType(Wall);
	newBoard->GetField(11, 10)->SetTerrainType(Wall);

	return newBoard;
}
