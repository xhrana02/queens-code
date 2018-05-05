//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Board.h"
#include "ModelLoader.h"

class BoardFactory
{
	static void PopulateNewBoard(Board* newBoard, fsg::ModelLoader* modelLoader);
public:
	static std::shared_ptr<Board> CreateStandardBoard(fsg::ModelLoader* modelLoader);
	static std::shared_ptr<Board> CreateTrainingDuelBoard(fsg::ModelLoader* modelLoader);
	static std::shared_ptr<Board> CreateChessBoard(fsg::ModelLoader* modelLoader);
};
