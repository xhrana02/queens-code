//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
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
