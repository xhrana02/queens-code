//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include <list>

class Unit
{
protected:
	Unit();

	int currentHitPoints = 0;
	int maximumHitPoints = 0;
	int currentEnergy = 0;
	int &maximumEnergy = currentHitPoints;

	void checkCurrentHitPoints();
	void checkCurrentEnergy();

	int damageReduction = 0;
	int damageReductionHP = 0;
	int damageReductionEN = 0;

public:
	virtual ~Unit() = default;
	virtual std::list<int>* GetListOfAbilites() = 0;

	int GetCurrentHitPoints()
	{
		checkCurrentHitPoints();
		return currentHitPoints;
	}
	int GetMaximumHitPoints() const
	{
		return maximumHitPoints;
	}
	int GetCurrentEnergy()
	{
		checkCurrentEnergy();
		return currentEnergy;
	}
	int GetMaximumEnergy() const
	{
		return maximumEnergy;
	}

	bool IsUnitAlive() const
	{
		return currentHitPoints > 0;
	}

	int TakeDamage(int damage);
	int TakeDamageHP(int damage, bool noReductions = false);
	int TakeDamageEN(int damage, bool noReductions = false);
};
