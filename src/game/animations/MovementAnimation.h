//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "AbilityAnimation.h"
#include <forward_list>

class Unit;
class Field;

class MovementAnimation : public AbilityAnimation
{
	Unit* movingUnit;
	std::forward_list<Field*> path;
	int framesPerTile;
	bool trackCamera;
public:
	MovementAnimation(Game* inGame, Unit* inUnit,std::forward_list<Field*> inPath, int inFramesPerTile = 10, bool inTrackCamera = true);
	bool Iteration() override;
};
