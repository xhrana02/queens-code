//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
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
