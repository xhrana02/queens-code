//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Unit.h"

Unit::Unit()
{
	currentHitPoints = maximumHitPoints;
	currentEnergy = maximumEnergy;
}

void Unit::checkCurrentHitPoints()
{
	if (currentHitPoints > GetMaximumHitPoints())
	{
		currentHitPoints = GetMaximumHitPoints();
	}
}

void Unit::checkCurrentEnergy()
{
	if (currentEnergy > GetMaximumEnergy())
	{
		currentEnergy = GetMaximumEnergy();
	}
}

int Unit::TakeDamage(int damage)
{
	auto dealtToEN = 0;
	auto dealtToHP = 0;
	auto damageEN = damage - damageReduction - damageReductionEN;
	if (damageEN > 0)
	{
		dealtToEN = TakeDamageEN(damageEN, true);
		auto damageHP = damageEN - dealtToEN - damageReductionHP;
		if(damageHP > 0)
		{
			dealtToHP = TakeDamageHP(damageHP, true);
		}
	}
	return dealtToEN + dealtToHP;
}

int Unit::TakeDamageHP(int damage, bool noReductions)
{
	if(!noReductions)
	{
		damage -= damageReductionHP;
	}

	if(damage <= 0)
	{
		return 0;
	}

	if(damage > GetCurrentHitPoints())
	{
		damage = currentHitPoints;
	}
	
	currentHitPoints -= damage;

	return damage;
}

int Unit::TakeDamageEN(int damage, bool noReductions)
{
	if (!noReductions)
	{
		damage -= damageReductionEN;
	}

	if (damage <= 0)
	{
		return 0;
	}

	if (damage > GetCurrentEnergy())
	{
		damage = currentEnergy;
	}

	currentEnergy -= damage;

	return damage;
}




