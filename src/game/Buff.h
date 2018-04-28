//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

class Unit;

class Buff
{
protected:
	int maxDuration = 1;
	int remainingDuration = 0;
	Unit* affectedUnit = nullptr;

	virtual void onEffectStart() = 0;
	virtual void onEffectEnd() = 0;
public:
	virtual ~Buff() = default;

	void StartEffect(Unit* buffTarget);
	bool OnTurnStart();

	int GetRemainingDuration() const
	{
		return remainingDuration;
	}
};
