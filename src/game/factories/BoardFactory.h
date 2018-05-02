//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Board.h"
#include "ModelLoader.h"

class BoardFactory
{
public:
	static std::shared_ptr<Board> CreateStandardBoard(fsg::ModelLoader* modelLoader);
	static std::shared_ptr<Board> CreateTrainingDuelBoard(fsg::ModelLoader* modelLoader);
	static std::shared_ptr<Board> CreateChessBoard(fsg::ModelLoader* modelLoader);
};
