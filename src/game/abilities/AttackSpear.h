//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "AttackLine.h"
#include "CommonTooltips.h"

class AttackSpear : public AttackLine
{
public:
	AttackSpear()
	{
		costEN = 4;
		damageNormal = 4;
		damageHP = 3;
		rangeMin = 1;
		rangeMax = 2;
		name = "Spear Attack";
		iconPath = "icons/AttackSpear.png";
		description = "<b><u>Spear Attack</u> ( 4 EN ) Line 1-2</b><br><br>"
			"Deals 3 HP and 4 normal damage to the target.<br>"
			HP_DAMAGE_TOOLTIP
			NORMAL_DAMAGE_TOOLTIP
			COMBINED_DAMAGE_TOOLTIP;
	}
};
