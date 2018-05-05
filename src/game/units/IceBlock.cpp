//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "IceBlock.h"
#include "Field.h"
#include "Player.h"


IceBlock::IceBlock()
{
	name = "Ice Block";
	this->maximumHP = 1;
	currentHP = maximumHP;
	currentEN = 0;
}

PlayerID IceBlock::GetOwnerID() const
{
	return Neutral;
}

fsg::RenderingObject* IceBlock::GetRenderingObject() const
{
	return iceBlockObject;
}

void IceBlock::SetIceBlockObject(fsg::RenderingObject* newRenderingObject)
{
	iceBlockObject = newRenderingObject;
}

int IceBlock::TakeDamage(AttackType attackType, int damageNormal, int damageHP, int damageEN)
{
	GetOccupiedField()->IceBlockDestroyed();
	return 0;
}
