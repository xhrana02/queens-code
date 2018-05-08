//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Buff.h"

Buff::Buff(Unit* buffTarget)
{
	affectedUnit = buffTarget;
}

void Buff::StartEffect()
{
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
