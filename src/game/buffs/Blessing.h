//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Buff.h"

class Blessing : public Buff
{
    void onEffectStart() override;
    void onEffectEnd() override;
    static int const enRegenIncrease = 1;
    static int const armorIncrease = 1;
public:
    Blessing();
};