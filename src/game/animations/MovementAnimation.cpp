//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "MovementAnimation.h"
#include "Field.h"
#include "Unit.h"
#include "Game.h"

using namespace std;

MovementAnimation::MovementAnimation(Game* inGame, Unit* inUnit, forward_list<Field*> inPath, int inFramesPerTile, bool inTrackCamera)
{
	movingUnit = inUnit;
	path = inPath;
	progress = 0;
	framesPerTile = inFramesPerTile;
	trackCamera = inTrackCamera;
	goal = (int(distance(path.begin(), path.end())) - 1) * framesPerTile;
	LockGame(inGame);
}

bool MovementAnimation::Iteration()
{
	// Establish fromField and toField
	auto iterator = path.begin();
	auto fieldIndex = progress / framesPerTile;
	advance(iterator, fieldIndex);
	auto fromField = *iterator;
	advance(iterator, 1);
	auto toField = *iterator;

	// Position the unit model between them
	auto fieldProgress = (progress % framesPerTile) / float(framesPerTile);
	auto posX = fromField->GetRenderingPosX() * (1 - fieldProgress)
			  + toField->GetRenderingPosX() * fieldProgress;
	auto posZ = fromField->GetRenderingPosZ() * (1 - fieldProgress)
		      + toField->GetRenderingPosZ() * fieldProgress;

	movingUnit->SetCustomRenderingObjectPosition(posX, posZ, 0.0f);
	if (trackCamera)
	{
		game->PanCameraToPosition(posX, posZ);
	}

	progress++;
	if (progress == goal)
	{
		movingUnit->SetCustomRenderingObjectPosition(
			toField->GetRenderingPosX(),
			toField->GetRenderingPosZ(),
			0.0f);
		return true;
	}
	return false;
}
