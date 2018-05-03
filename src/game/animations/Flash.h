//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "AbilityAnimation.h"
#include <glm/detail/type_vec4.hpp>

class Unit;
class Field;
namespace fsg
{
	class RenderingObject;
}

class Flash : public AbilityAnimation
{
	int subgoal = 0;
	fsg::RenderingObject* flashingUnit;
	glm::vec4 normalColor;
	glm::vec4 flashColor;
public:
	Flash(Game* inGame, Unit* inUnit, glm::vec4 color, int intensity, int customPeakFrame = 3);
	bool Iteration() override;
};
