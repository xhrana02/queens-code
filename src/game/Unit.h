//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include <list>
#include <memory>
#include "RenderingObject.h"

using namespace std;
using namespace fsg;

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

	shared_ptr<RenderingObject> renderingObject;

public:
	virtual ~Unit() = default;
	virtual list<int>* GetListOfAbilites() = 0;
	
	RenderingObject* GetRenderingObject() const
	{
		return renderingObject.get();
	}
	void SetRenderingObject(RenderingObject* newObject)
	{
		renderingObject = shared_ptr<RenderingObject>(newObject);
	}

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
