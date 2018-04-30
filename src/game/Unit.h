//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Ability.h"
#include "Buff.h"
#include "RenderingObject.h"
#include <memory>
#include <QObject>

class QQuickItem;
class QQmlEngine;
class Field;
class ApplicationControl;
class Player;

class Unit
{
protected:
	ApplicationControl* appControl = nullptr;

	QString name;
	bool isRoyalty = false;
	Player* owner = nullptr;

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

	std::vector<Buff*> buffs = std::vector<Buff*>();

	Field* occupiedField = nullptr;

	std::shared_ptr<fsg::RenderingObject> renderingObject;
	QQuickItem* infoBar = nullptr;
	int currentHpTheory = 0;
	int currentEnTheory = 0;
	QQuickItem* abilitiesBar = nullptr;

public:
	~Unit();
	void SetAppControl(ApplicationControl* inAppControl)
	{
		appControl = inAppControl;
	}
	void GamePopup(QString message) const;

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
	void SelectedUnitOnFieldHovered(Field* hoveredField);

	QString GetName() const
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

	bool IsRoyalty() const
	{
		return isRoyalty;
	}

	Player* GetOwner() const
	{
		return owner;
	}
	void SetOwner(Player* player)
	{
		owner = player;
	}

	void CreateInfoBar(QQmlEngine* engine, QQuickItem* guiRoot);
	void UpdateInfoBar(glm::mat4 perspective, glm::mat4 view, int winWidth, int winHeight, float fluctuation) const;
	void CreateAbilitiesBar(QQmlEngine* engine, QQuickItem* guiRoot);

	void Select(bool isEnemy = false) const;
	void Unselect() const;
	void SelectAbility(int slot) const;
	void OnAbilitySelected(int slot);
	void RefreshAbilityHalflight();
	bool UseSelectedAbility(Field* target);
	bool IsEnemy(Unit* unit) const;

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
	void IncreaseArmor(int amount)
	{
		damageReduction += amount;
	}
	void DecreaseArmor(int amount)
	{
		damageReduction -= amount;
	}
	void IncreaseRegenerationHP(int amount)
	{
		regenerationHP += amount;
	}
	void DecreaseRegenerationHP(int amount)
	{
		regenerationHP -= amount;
	}
	void IncreaseRegenerationEN(int amount)
	{
		regenerationEN += amount;
	}
	void DecreaseRegenerationEN(int amount)
	{
		regenerationEN -= amount;
	}
	void IncreaseRestHP(int amount)
	{
		restHP += amount;
	}
	void DecreaseRestHP(int amount)
	{
		restHP -= amount;
	}
	void IncreaseRestEN(int amount)
	{
		restEN += amount;
	}
	void DecreaseRestEN(int amount)
	{
		restEN -= amount;
	}

	bool IsUnitAlive() const
	{
		return currentHP > 0;
	}
	void OnUnitDeath();

	int TakeDamage(int damageNormal, int damageEN = 0, int damageHP = 0);
	int Heal(int healHP, int healEN = 0);
	void Stun(int duration);
	void MakeRestless(int duration);

	std::vector<std::shared_ptr<Ability>> GetAbilites() const
	{
		return abilities;
	}
	std::vector<Buff*> GetActiveBuffs() const
	{
		return buffs;
	}
	void ApplyBuff(Buff* newBuff);
	void CheckBuffDurations();

	void OnTurnBegin();
	void OnTurnEnd();

	// THEORY METHODS
	void ResetTheory();
	int ReduceTheoreticalHP(int amount);
	int ReduceTheoreticalEN(int amount);
	int RegainTheoreticalHP(int amount);
	int RegainTheoreticalEN(int amount);
	void TakeTheoreticalDamage(int damageNormal, int damageEN = 0, int damageHP = 0);
	void TheoreticalHeal(int healHP, int healEN = 0);
};
