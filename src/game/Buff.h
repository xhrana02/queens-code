//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include <QString>
#include "GameEnums.h"

class Unit;

class Buff
{
protected:
    BuffID id;
    int maxDuration = 1;
    int remainingDuration = 0;
    Unit* affectedUnit = nullptr;

    virtual void onEffectStart() = 0;
    virtual void onEffectEnd() = 0;
public:
    virtual ~Buff() = default;
	explicit Buff(Unit* buffTarget);

    void StartEffect();
    bool OnTurnStart();

    BuffID GetID() const
    {
        return id;
    }

    int GetRemainingDuration() const
    {
        return remainingDuration;
    }
	void SetRemainingDuration(int newDuration)
	{
		remainingDuration = newDuration;
	}

    int GetMaximumDuration() const
    {
        return maxDuration;
    }

    void RestartDuration()
    {
        remainingDuration = maxDuration;
    }
};
