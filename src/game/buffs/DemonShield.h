//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
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