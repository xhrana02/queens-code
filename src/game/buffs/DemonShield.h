//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Buff.h"

class DemonShield : public Buff
{
    void onEffectStart() override;
    void onEffectEnd() override;
    static int const armorIncrease = 6;
public:
	explicit DemonShield(Unit* buffTarget);
};