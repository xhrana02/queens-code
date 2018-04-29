//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
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