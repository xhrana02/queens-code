//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "AttackMelee.h"
#include "CommonTooltips.h"

class AttackDagger : public AttackMelee
{
public:
	AttackDagger()
	{
		costEN = 2;
		damageHP = 5;
		name = "Dagger Attack";
		iconPath = "icons/AttackDagger.png";
		description = "<b><u>Dagger Attack</u> ( 2 EN ) Melee</b><br><br>"
			"Deals 5 HP damage to the target.<br>"
			HP_DAMAGE_TOOLTIP;
	}
};
