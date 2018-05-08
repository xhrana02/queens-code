//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
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
