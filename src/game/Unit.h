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
#include "GameEnums.h"

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
	Player* owner = nullptr;

	int currentHP = 0;
	int maximumHP = 0;
	int currentEN = 0;
	int &maximumEN = currentHP;
	void checkCurrentHitPoints();
	void checkCurrentEnergy();

	int armor = 0;
	float damageModifierLine = 1.0f;
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
	virtual ~Unit();
	void SetAppControl(ApplicationControl* inAppControl)
	{
		appControl = inAppControl;
	}
	void GamePopup(QString message) const;

	float GetRenderingPosX() const;
	float GetRenderingPosZ() const;
	virtual fsg::RenderingObject* GetRenderingObject() const
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

	Player* GetOwner() const
	{
		return owner;
	}
	virtual PlayerID GetOwnerID() const;
	void SetOwner(Player* player);

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
		armor += amount;
	}
	void DecreaseArmor(int amount)
	{
		armor -= amount;
	}
	void IncreaseDamageReductionLine(float amount)
	{
		damageModifierLine *= 1.0f - amount;
	}
	void DecreaseDamageReductionLine(float amount)
	{
		damageModifierLine /= 1.0f - amount;
	}
	float GetDamageReductionLine() const
	{
		return 1.0f - damageModifierLine;
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
	virtual void OnUnitDeath();

	virtual int TakeDamage(AttackType attackType, int damageNormal, int damageHP = 0, int damageEN = 0);
	virtual int Heal(int healHP, int healEN = 0);
	void Stun(int duration);
	void MakeRestless(int duration);
	void OnFreezeEnd();

	bool IsStunned() const
	{
		return stunned;
	}
	bool IsRestless() const
	{
		return restless;
	}
	
	std::vector<std::shared_ptr<Ability>> GetAbilites() const
	{
		return abilities;
	}
	std::vector<Buff*> GetActiveBuffs() const
	{
		return buffs;
	}
	virtual void ApplyBuff(Buff* newBuff);
	void CheckBuffDurations();
	void CheckStatusDurations();
	void CheckThroneClaim() const;

	void OnTurnBegin();
	void OnTurnEnd();

	// THEORY METHODS
	void ResetTheory();
	int ReduceTheoreticalHP(int amount);
	int ReduceTheoreticalEN(int amount);
	int RegainTheoreticalHP(int amount);
	int RegainTheoreticalEN(int amount);
	virtual int TakeTheoreticalDamage(AttackType attackType, int damageNormal, int damageHP = 0, int damageEN = 0);
	virtual int TheoreticalHeal(int healHP, int healEN = 0);

	// PASSIVE ABILITIES RELATED PROPERTIES
	bool IsRoyalty = false;
	bool HasOpportunityAttack = false;
	int DamageOpportunityAttack = 0;
};
