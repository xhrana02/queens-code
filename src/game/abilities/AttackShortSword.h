//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "AttackMelee.h"
#include "CommonTooltips.h"

class AttackShortSword : public AttackMelee
{
public:
	AttackShortSword()
	{
		costEN = 3;
		damageNormal = 7;
		name = "Short Sword Attack";
		iconPath = "icons/AttackShortSword.png";
		description = "<b><u>Short Sword Attack</u> ( 3 EN ) Melee</b><br><br>"
			"Deals 7 normal damage to the target.<br>"
			NORMAL_DAMAGE_TOOLTIP;
	}
};
