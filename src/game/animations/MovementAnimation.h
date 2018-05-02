//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
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
