//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "Buff.h"

class Blessing : public Buff
{
	void onEffectStart() override;
	void onEffectEnd() override;

public:
	Blessing();

};