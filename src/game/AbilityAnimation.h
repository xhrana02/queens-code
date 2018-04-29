//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

class Game;

class AbilityAnimation
{
protected:
	Game* game = nullptr;
	int progress = 0;
	int goal = 0;
public:
	virtual ~AbilityAnimation() = default;
	bool LockGame(Game* inGame);
	virtual bool Iteration() = 0;
};