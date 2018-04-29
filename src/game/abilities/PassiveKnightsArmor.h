//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "PassiveAbility.h"
#include "CommonTooltips.h"

class PassiveKnightsArmor : public PassiveAbility
{
public:
	PassiveKnightsArmor::PassiveKnightsArmor()
	{
		name = "Knight's Armor";
		iconPath = "icons/PassiveKnightsArmor.png";
		description = "<b><u>Knight's Armor</u> ( passive )</b><br><br>"
			"The knight has bonus 2 Armor.<br><br>"
			ARMOR_TOOLTIP;
	}
};
