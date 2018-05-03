//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Unit.h"
#include "Board.h"
#include "Field.h"
#include <QtQml>
#include "../ApplicationControl.h"
#include "Flash.h"

using namespace std;
using namespace fsg;
using namespace glm;

Unit::~Unit()
{
	infoBar->deleteLater();
	abilitiesBar->deleteLater();
	for (auto buff : buffs)
	{
		delete buff;
	}
}

void Unit::GamePopup(QString message) const
{
	if (appControl != nullptr)
	{
		appControl->ConsoleWrite(message);
		appControl->GamePopup(message);
	}
}

/**
* \brief Rendering position X.
*/
float Unit::GetRenderingPosX() const
{
	return occupiedField->GetRenderingPosX();
}

/**
* \brief Rendering position Z (Z in rendering coords, Y in game coords).
*/
float Unit::GetRenderingPosZ() const
{
	return occupiedField->GetRenderingPosZ();
}

void Unit::UpdateRenderingObjectPosition() const
{
	renderingObject->position = vec3(GetRenderingPosX(), 0.0f, GetRenderingPosZ());
}

void Unit::SetCustomRenderingObjectPosition(float x, float z, float up) const
{
	renderingObject->position = vec3(x, up, z);
}

void Unit::SelectedUnitOnFieldHovered(Field* hoveredField)
{
	if (selectedAbility == nullptr)
	{
		GetBoard()->HighlightField(hoveredField);
	}
	else
	{
		selectedAbility->SelectedAbilityOnFieldHovered(GetBoard(), this, hoveredField);
	}
}

Board* Unit::GetBoard() const
{
	if(occupiedField != nullptr)
	{
		auto board = occupiedField->GetBoard();
		if (board == nullptr)
		{
			throw exception("Unit GetBoard - This unit's field doesn't belong to a board. Weird.");
		}
		return board;
	}
	throw exception("Unit GetBoard - This unit doesn't occupy a field. Weird.");
}

void Unit::CreateInfoBar(QQmlEngine* engine, QQuickItem* guiRoot)
{
	if(infoBar != nullptr)
	{
		infoBar->deleteLater();
	}
	QQmlComponent component(engine,
		QUrl::fromLocalFile(APP_RESOURCES"/qml/UnitInfoBar.qml"));
	infoBar = qobject_cast<QQuickItem*>(component.create());
	infoBar->setParentItem(guiRoot);

	QVariant returnedValue;
	QMetaObject::invokeMethod(infoBar, "setUnitConstants",
		Q_RETURN_ARG(QVariant, returnedValue),
		Q_ARG(QVariant, name),
		Q_ARG(QVariant, maximumHP));
}

void Unit::UpdateInfoBar(mat4 perspective, mat4 view, int winWidth, int winHeight, float fluctuation) const
{
	auto homopos = perspective * view * vec4(GetRenderingPosX(), 1.2f, GetRenderingPosZ(), 1.0f);
	auto posvec = vec3(homopos.x / homopos.w, homopos.y / homopos.w, homopos.z / homopos.w);
	auto posX = ((posvec.x + 1) / 2.0f) * winWidth - 60;
	auto posY = ((1 - posvec.y) / 2.0f) * winHeight - 19;
	auto depth = 1 - posvec.z;
	auto size = depth * (winWidth + winHeight) / 500.0f;
	auto blessedDuration = 0;
	auto shieldedDuration = 0;
	for (auto buff : buffs)
	{
		if (buff->GetName() == "Blessing")
		{
			blessedDuration = buff->GetRemainingDuration();
		}
		if (buff->GetName() == "Demon Shield")
		{
			shieldedDuration = buff->GetRemainingDuration();
		}
	}

	QVariant returnedValue;
	if (posvec.z < 0 || posvec.z > 1)
	{
		QMetaObject::invokeMethod(infoBar, "hide",
			Q_RETURN_ARG(QVariant, returnedValue));
	}
	else
	{
		QMetaObject::invokeMethod(infoBar, "show",
			Q_RETURN_ARG(QVariant, returnedValue));
		QMetaObject::invokeMethod(infoBar, "updatePosition",
			Q_RETURN_ARG(QVariant, returnedValue),
			Q_ARG(QVariant, posX),
			Q_ARG(QVariant, posY),
			Q_ARG(QVariant, depth),
			Q_ARG(QVariant, size)
		);
		QMetaObject::invokeMethod(infoBar, "updateValues",
			Q_RETURN_ARG(QVariant, returnedValue),
			Q_ARG(QVariant, currentHP),
			Q_ARG(QVariant, currentEN)
		);
		QMetaObject::invokeMethod(infoBar, "updateTheoryValues",
			Q_RETURN_ARG(QVariant, returnedValue),
			Q_ARG(QVariant, currentHpTheory),
			Q_ARG(QVariant, currentEnTheory),
			Q_ARG(QVariant, fluctuation)
		);
		QMetaObject::invokeMethod(infoBar, "updateStatus",
			Q_RETURN_ARG(QVariant, returnedValue),
			Q_ARG(QVariant, stunDuration),
			Q_ARG(QVariant, restlessDuration),
			Q_ARG(QVariant, blessedDuration),
			Q_ARG(QVariant, shieldedDuration)
		);
	}

}

void Unit::CreateAbilitiesBar(QQmlEngine* engine, QQuickItem* guiRoot)
{
	if(abilitiesBar != nullptr)
	{
		abilitiesBar->deleteLater();
	}
	QQmlComponent component(engine,
		QUrl::fromLocalFile(APP_RESOURCES"/qml/UnitAbilitiesBar.qml"));
	abilitiesBar = qobject_cast<QQuickItem*>(component.create());
	abilitiesBar->setParentItem(guiRoot);
	QVariant returnedValue;
	auto slot = 0;
	for (auto ability : abilities)
	{
		slot++;
		QMetaObject::invokeMethod(abilitiesBar, "setAbility",
			Q_RETURN_ARG(QVariant, returnedValue),
			Q_ARG(QVariant, slot),
			Q_ARG(QVariant, ability->GetName()),
			Q_ARG(QVariant, ability->GetIconPath()),
			Q_ARG(QVariant, ability->GetDescription()),
			Q_ARG(QVariant, !ability->IsPassive())
		);
	}
}

void Unit::Select(bool isEnemy) const
{
	renderingObject->Select();
	if (!isEnemy)
	{
		QVariant returnedValue;
		QMetaObject::invokeMethod(abilitiesBar, "show",
			Q_RETURN_ARG(QVariant, returnedValue));
	}

	if (appControl != nullptr)
	{
		appControl->OnUnitSelected(name);
	}
}

void Unit::Unselect() const
{
	renderingObject->Unselect();
	QVariant returnedValue;
	QMetaObject::invokeMethod(abilitiesBar, "hide",
		Q_RETURN_ARG(QVariant, returnedValue));

	if (appControl != nullptr)
	{
		appControl->OnUnitUnselected();
	}
}

void Unit::SelectAbility(int slot) const
{
	QVariant returnedValue;
	QMetaObject::invokeMethod(abilitiesBar, "selectAbility",
		Q_RETURN_ARG(QVariant, returnedValue),
		Q_ARG(QVariant, slot));
}

void Unit::OnAbilitySelected(int slot)
{
	auto newSelectedAbility = abilities[slot - 1].get();

	if(newSelectedAbility->CanAfford(this) && !stunned)
	{
		if(slot != selectedAbilitySlot)
		{
			selectedAbilitySlot = slot;
			selectedAbility = newSelectedAbility;
		}
		RefreshAbilityHalflight();
	}
	else
	{
		selectedAbilitySlot = 0;
		selectedAbility = nullptr;
		GetBoard()->UnhalflightAllFields();
		QVariant returnedValue;
		QMetaObject::invokeMethod(abilitiesBar, "unselectAll",
			Q_RETURN_ARG(QVariant, returnedValue));
		if (stunned)
		{
			GamePopup("This unit is Stunned and cannot take any action");
		}
		else
		{
			GamePopup("Not enough EN (or HP) to use " + newSelectedAbility->GetName());
		}
	}
}

void Unit::RefreshAbilityHalflight()
{
	selectedAbility->OnSelected(GetBoard(), this);
}

bool Unit::UseSelectedAbility(Field* target)
{
	if (stunned)
	{
		GamePopup("This unit is Stunned and cannot take any action");
		return false;
	}
	if (selectedAbilitySlot == 0)
	{
		GamePopup("No ability selected");
		return false;
	}
	movedThisTurn = true;
	return abilities[selectedAbilitySlot - 1]->Effect(GetBoard(), this, target);
}

bool Unit::IsEnemy(Unit* unit) const
{
	return owner->GetID() != unit->GetOwner()->GetID();
}

void Unit::checkCurrentHitPoints()
{
	if (currentHP > maximumHP)
	{
		currentHP = maximumHP;
	}
}

void Unit::checkCurrentEnergy()
{
	if (currentEN > maximumEN)
	{
		currentEN = maximumEN;
	}
}

int Unit::ReduceHP(int amount)
{
	if(amount <= 0)
	{
		return 0;
	}

	if(amount > GetCurrentHitPoints())
	{
		amount = currentHP;
	}

	currentHP -= amount;

	return amount;
}

int Unit::ReduceEN(int amount)
{
	if (amount <= 0)
	{
		return 0;
	}

	if (amount > GetCurrentEnergy())
	{
		amount = currentEN;
	}

	currentEN -= amount;

	return amount;
}

int Unit::RegainHP(int amount)
{
	if (amount <= 0)
	{
		return 0;
	}
	if (currentHP + amount > maximumHP)
	{
		amount = maximumHP - currentHP;
	}
	
	currentHP += amount;

	return amount;
}

int Unit::RegainEN(int amount)
{
	if (amount <= 0)
	{
		return 0;
	}
	if (currentEN + amount > maximumEN)
	{
		amount = maximumEN - currentEN;
	}

	currentEN += amount;

	return amount;
}


void Unit::OnUnitDeath()
{
	occupiedField->UnitLeavesThisField();
	QVariant returnedValue;
	QMetaObject::invokeMethod(infoBar, "hide",
		Q_RETURN_ARG(QVariant, returnedValue));
	owner->OnUnitDeath(this);
}

int Unit::TakeDamage(AttackType attackType, int damageNormal, int damageHP, int damageEN)
{
	auto dealtToEN = 0;
	auto dealtToHP = 0;

	if (attackType == Line)
	{
		auto damageTotal = damageNormal + damageHP + damageEN;
		auto damageReducedLine = floor(damageTotal * GetDamageReductionLine());
		damageNormal -= damageReducedLine;
	}

	damageNormal -= armor;
	if (damageNormal < 0)
	{
		damageEN += damageNormal;
		damageNormal = 0;
		if (damageEN < 0)
		{
			damageHP += damageEN;
			damageEN = 0;
			if (damageHP < 0)
			{
				return 0;
			}
		}
	}

	if (damageHP > 0)
	{
		dealtToHP += ReduceHP(damageHP);
	}

	if (damageEN > 0)
	{
		dealtToEN += ReduceEN(damageEN);
	}

	if (damageNormal > 0)
	{
		auto ENpart = ReduceEN(damageNormal);
		dealtToEN += ENpart;
		damageNormal -= ENpart;
		if (damageNormal > 0)
		{
			dealtToHP += ReduceHP(damageNormal);
		}
	}

	return dealtToEN + dealtToHP;
}

int Unit::Heal(int healHP, int healEN)
{
	return RegainHP(healHP) + RegainEN(healEN);
}

void Unit::regenerate()
{
	RegainHP(regenerationHP);
	RegainEN(regenerationEN);
}

void Unit::rest()
{
	if (!restless)
	{
		RegainHP(restHP);
		RegainEN(restEN);
	}
}

void Unit::Stun(int duration)
{
	if(duration > stunDuration)
	{
		stunned = true;
		stunDuration = duration;
		MakeRestless(duration);
	}
}

void Unit::MakeRestless(int duration)
{
	if(duration > restlessDuration)
	{
		restless = true;
		restlessDuration = duration;
	}
}

void Unit::ApplyBuff(Buff* newBuff)
{
	buffs.push_back(newBuff);
	newBuff->StartEffect(this);
}

void Unit::CheckBuffDurations()
{
	for (auto iterator = buffs.begin(); iterator != buffs.end();)
	{
		auto buff = *iterator;

		auto buffEnded = buff->OnTurnStart();
		if (buffEnded)
		{
			iterator = buffs.erase(iterator);
			delete buff;
		}
		else
		{
			++iterator;
		}
	}
}

void Unit::CheckStatusDurations()
{
	// Reduce restless and stunned durations by 1
	if (restless)
	{
		restlessDuration--;
		if (restlessDuration <= 0)
		{
			restless = false;
		}
		// This is inside the restless if because stunned units are also restless
		if (stunned)
		{
			stunDuration--;
			if (stunDuration <= 0)
			{
				stunned = false;
			}
		}
	}

	// Units in ice blocks become restunned
	if (occupiedField->GetTerrainType() == IceBlock)
	{
		Stun(1);
	}
}

void Unit::CheckThroneClaim() const
{
	// Queen sitting on the throne makes all enemies Restless
	if (IsRoyalty && !stunned)
	{
		if (occupiedField->GetTerrainType() == Throne)
		{
			auto enemyUnits = owner->GetEnemyPlayer()->GetUnits();
			for (auto enemy : enemyUnits)
			{
				enemy->MakeRestless(1);
				if (appControl != nullptr)
				{
					auto game = appControl->GetGame();
					// ReSharper disable once CppNonReclaimedResourceAcquisition
					new Flash(game, enemy, vec4(0.0f, 0.0f, 0.0f, 0.75f), 10);
				}
			}
		}
	}
}

void Unit::OnTurnBegin()
{
	movedThisTurn = false;
	// The order of these is very important!!!
	regenerate();
	CheckBuffDurations();
}

void Unit::OnTurnEnd()
{
	// The order of these is very important!!!
	CheckThroneClaim();
	// Rest if the unit didn't move this turn
	if (!movedThisTurn)
	{
		rest();
	}
	CheckStatusDurations();
}


////////////////////////////////////////////////////////////////////////////////
// THEORY METHODS

void Unit::ResetTheory()
{
	currentHpTheory = currentHP;
	currentEnTheory = currentEN;
}


int Unit::ReduceTheoreticalHP(int amount)
{
	if(amount <= 0)
	{
		return 0;
	}

	if(amount > currentHpTheory)
	{
		amount = currentHpTheory;
	}

	currentHpTheory -= amount;

	return amount;
}

int Unit::ReduceTheoreticalEN(int amount)
{
	if (amount <= 0)
	{
		return 0;
	}

	if (amount > currentEnTheory)
	{
		amount = currentEnTheory;
	}

	currentEnTheory -= amount;

	return amount;
}

int Unit::RegainTheoreticalHP(int amount)
{
	if (amount <= 0)
	{
		return 0;
	}
	if (currentHpTheory + amount > maximumHP)
	{
		amount = maximumHP - currentHpTheory;
	}

	currentHpTheory += amount;

	return amount;
}

int Unit::RegainTheoreticalEN(int amount)
{
	if (amount <= 0)
	{
		return 0;
	}
	if (currentEnTheory + amount > maximumEN)
	{
		amount = maximumEN - currentEnTheory;
	}

	currentEnTheory += amount;

	return amount;
}

void Unit::TakeTheoreticalDamage(AttackType attackType, int damageNormal, int damageHP, int damageEN)
{
	if (attackType == Line)
	{
		auto damageTotal = damageNormal + damageHP + damageEN;
		auto damageReducedLine = floor(damageTotal * GetDamageReductionLine());
		damageNormal -= damageReducedLine;
	}
	damageNormal -= armor;
	if (damageNormal < 0)
	{
		damageEN += damageNormal;
		damageNormal = 0;
		if (damageEN < 0)
		{
			damageHP += damageEN;
			damageEN = 0;
			if (damageHP < 0)
			{
				return;
			}
		}
	}

	if (damageHP > 0)
	{
		ReduceTheoreticalHP(damageHP);
	}

	if (damageEN > 0)
	{
		ReduceTheoreticalEN(damageEN);
	}

	if (damageNormal > 0)
	{
		auto ENpart = ReduceTheoreticalEN(damageNormal);
		damageNormal -= ENpart;
		if (damageNormal > 0)
		{
			ReduceTheoreticalHP(damageNormal);
		}
	}
}

void Unit::TheoreticalHeal(int healHP, int healEN)
{
	RegainTheoreticalHP(healHP) + RegainTheoreticalEN(healEN);
}


