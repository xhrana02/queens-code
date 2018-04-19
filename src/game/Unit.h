//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include <memory>
#include "RenderingObject.h"
#include "Ability.h"

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

	std::shared_ptr<fsg::RenderingObject> renderingObject;

public:
	virtual ~Unit() = default;
	virtual std::vector<Ability>* GetListOfAbilites() = 0;

	fsg::RenderingObject* GetRenderingObject() const
	{
		return renderingObject.get();
	}
	void SetRenderingObject(fsg::RenderingObject* newObject)
	{
		renderingObject = std::shared_ptr<fsg::RenderingObject>(newObject);
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
