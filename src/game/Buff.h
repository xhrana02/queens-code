//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include <QString>

class Unit;

class Buff
{
protected:
    QString name = "";

    int maxDuration = 1;
    int remainingDuration = 0;
    Unit* affectedUnit = nullptr;

    virtual void onEffectStart() = 0;
    virtual void onEffectEnd() = 0;
public:
    virtual ~Buff() = default;

    void StartEffect(Unit* buffTarget);
    bool OnTurnStart();

    QString GetName() const
    {
        return name;
    }

    int GetRemainingDuration() const
    {
        return remainingDuration;
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
