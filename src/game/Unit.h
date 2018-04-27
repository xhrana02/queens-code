//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "GameEnums.h"
#include "Ability.h"
#include "RenderingObject.h"
#include <memory>
#include <QObject>

class QQuickItem;
class QQmlEngine;
class Field;
class ApplicationControl;

class Unit
{
protected:
	ApplicationControl* appControl = nullptr;

	std::string name;
	PlayerID ownerID = Player1;

	int currentHP = 0;
	int maximumHP = 0;
	int currentEN = 0;
	int &maximumEN = currentHP;
	void checkCurrentHitPoints();
	void checkCurrentEnergy();

	int damageReduction = 0;
	int regenerationHP = 0;
	int regenerationEN = 3;
	int restHP = 1;
	int restEN = 3;

	void regenerate();
	void rest();

	bool stunned = false;
	int stunDuration = 0;
	bool restless = false;
	int restlessDuration = 0;

	bool movedThisTurn = false;

	std::vector<std::shared_ptr<Ability>> abilities = std::vector<std::shared_ptr<Ability>>();
	int selectedAbilitySlot = 0;
	Ability* selectedAbility = nullptr;

	Field* occupiedField = nullptr;

	std::shared_ptr<fsg::RenderingObject> renderingObject;
	QQuickItem* infoBar = nullptr;
	QQuickItem* abilitiesBar = nullptr;

public:
	~Unit();
	void SetAppControl(ApplicationControl* inAppControl)
	{
		appControl = inAppControl;
	}
	void SendToConsole(QString message) const;

	float GetRenderingPosX() const;
	float GetRenderingPosZ() const;
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

	std::string GetName() const
	{
		return name;
	}

	Field* GetOccupiedField() const
	{
		return occupiedField;
	}
	void SetOccupiedField(Field* newField)
	{
		occupiedField = newField;
	}
	Board* GetBoard() const;

	PlayerID GetOwner() const
	{
		return ownerID;
	}
	void SetOwner(PlayerID player)
	{
		ownerID = player;
	}

	void CreateInfoBar(QQmlEngine* engine, QQuickItem* guiRoot);
	void UpdateInfoBar(glm::mat4 perspective, glm::mat4 view, int winWidth, int winHeight) const;
	void CreateAbilitiesBar(QQmlEngine* engine, QQuickItem* guiRoot);

	void Select(bool isEnemy = false) const;
	void Unselect() const;
	void SelectAbility(int slot) const;
	void OnAbilitySelected(int slot);
	void RefreshAbilityHalflight();
	bool UseSelectedAbility(Field* target);

	int GetCurrentHitPoints()
	{
		checkCurrentHitPoints();
		return currentHP;
	}
	int GetMaximumHitPoints() const
	{
		return maximumHP;
	}
	int GetCurrentEnergy()
	{
		checkCurrentEnergy();
		return currentEN;
	}
	int GetMaximumEnergy() const
	{
		return maximumEN;
	}

	int ReduceHP(int amount);
	int ReduceEN(int amount);
	int RegainHP(int amount);
	int RegainEN(int amount);

	bool IsUnitAlive() const
	{
		return currentHP > 0;
	}

	int TakeDamage(int damageNormal, int damageEN = 0, int damageHP = 0);
	int Heal(int healHP, int healEN = 0);

	std::vector<std::shared_ptr<Ability>> GetAbilites() const
	{
		return abilities;
	}

	void OnTurnBegin();
	void OnTurnEnd();
};
