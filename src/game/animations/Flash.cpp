//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Flash.h"
#include "Unit.h"
#include "RenderingObject.h"

using namespace glm;

Flash::Flash(Game* inGame, Unit* inUnit, vec4 color, int intensity, int customPeakFrame)
{
	if (!inGame || !inUnit)
	{
		delete this;
		return;
	}
	goal = 5 * intensity;
	subgoal = customPeakFrame;
	flashingUnit = inUnit->GetRenderingObject();
	normalColor = flashingUnit->GetNormalColor();
	flashColor = color;
	flashingUnit->StartFlash();
	LockGame(inGame);
}

bool Flash::Iteration()
{
	if (progress < subgoal)
	{
		auto subgoalProgress = float(progress) / float(subgoal);
		flashingUnit->SetFlashColor(
			flashColor * subgoalProgress +
			normalColor * (1 - subgoalProgress)
		);
	}
	else
	{
		auto goalProgress = sin(radians(90.0f * float(progress - subgoal) / float(goal - subgoal)));
		flashingUnit->SetFlashColor(
			flashColor * (1 - goalProgress) +
			normalColor * goalProgress
		);
	}

	progress++;
	if (progress == goal)
	{
		flashingUnit->EndFlash();
		return true;
	}
	return false;
}
