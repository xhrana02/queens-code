//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Ability.h"
#include "RenderingObject.h"
#include <memory>
#include <QObject>

class QQuickItem;
class QQmlEngine;
class Field;

class Unit
{
protected:
	std::string name;

	int currentHitPoints = 0;
	int maximumHitPoints = 0;
	int currentEnergy = 0;
	int &maximumEnergy = currentHitPoints;

	void checkCurrentHitPoints();
	void checkCurrentEnergy();

	int damageReduction = 0;

	std::vector<std::shared_ptr<Ability>> abilities = std::vector<std::shared_ptr<Ability>>();

	Field* occupiedField = nullptr;

	std::shared_ptr<fsg::RenderingObject> renderingObject;
	QQuickItem* infoBar = nullptr;
	QQuickItem* abilitiesBar = nullptr;

	float GetRenderingPosX() const;
	float GetRenderingPosZ() const;
public:
	~Unit();

	fsg::RenderingObject* GetRenderingObject() const
	{
		return renderingObject.get();
	}
	void SetRenderingObject(std::shared_ptr<fsg::RenderingObject> newObject)
	{
		renderingObject = newObject;
	}
	void UpdateRenderingObjectPosition() const;
	void SetCustomRenderingObjectPosition(float x, float z, float up) const;

	void CreateInfoBar(QQmlEngine* engine, QQuickItem* guiRoot);
	void UpdateInfoBar(glm::mat4 perspective, glm::mat4 view, int winWidth, int winHeight) const;
	void CreateAbilitiesBar(QQmlEngine* engine, QQuickItem* guiRoot);

	void Select();
	void Unselect();

	std::string GetName() const
	{
		return name;
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

	int ReduceHP(int amount);
	int ReduceEN(int amount);

	bool IsUnitAlive() const
	{
		return currentHitPoints > 0;
	}

	int TakeDamage(int damageNormal, int damageEN = 0, int damageHP = 0);

	std::vector<std::shared_ptr<Ability>> GetAbilites() const
	{
		return abilities;
	}

	Field* GetOccupiedField() const
	{
		return occupiedField;
	}
	void SetOccupiedField(Field* newField)
	{
		occupiedField = newField;
	}
};
