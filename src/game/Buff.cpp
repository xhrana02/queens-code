//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Buff.h"

void Buff::StartEffect(Unit* buffTarget)
{
	affectedUnit = buffTarget;
	remainingDuration = maxDuration;
	onEffectStart();
}

/**
 * \brief Returns true if the buff ended (delete this object afterwards!). Returns false otherwise.
 */
bool Buff::OnTurnStart()
{
	remainingDuration--;
	if (remainingDuration <= 0)
	{
		onEffectEnd();
		return true;
	}
	return false;
}
