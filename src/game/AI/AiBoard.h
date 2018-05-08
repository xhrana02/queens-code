//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Board.h"

class AiGame;

class AiBoard : public Board
{
public:
	AiBoard(Board* source, AiGame* aiGame);

	void CopyField(Field* source, Field* target, AiGame* aiGame) const;
};
