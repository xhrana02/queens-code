//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
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