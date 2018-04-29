//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "PassiveAbility.h"
#include "CommonTooltips.h"

class PassiveThroneClaim : public PassiveAbility
{
public:
	PassiveThroneClaim::PassiveThroneClaim()
	{
		name = "Claim Throne";
		iconPath = "icons/PassiveThroneClaim.png";
		description = "<b><u>Claim Throne</u> ( passive )</b><br><br>"
			"When standing on the throne tile at the end of the turn, all enemy units become Restless for 1 turn.<br><br>"
			RESTLESS_TOOLTIP "<br>"
			REST_TOOLTIP;
	}
};
