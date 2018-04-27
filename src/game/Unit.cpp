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
#include <QQuickItem>
#include "../ApplicationControl.h"

using namespace std;
using namespace fsg;
using namespace glm;

Unit::~Unit()
{
	infoBar->deleteLater();
	abilitiesBar->deleteLater();
}

void Unit::SendToConsole(QString message) const
{
	if (appControl != nullptr)
	{
		appControl->ConsoleWrite(message);
	}
}

/**
* \brief Rendering position X.
*/
float Unit::GetRenderingPosX() const
{
	return occupiedField->GetX() - (occupiedField->GetBoard()->PlayableWidth() + 1) / 2.0f;
}

/**
* \brief Rendering position Z (Z in rendering coords, Y in game coords).
*/
float Unit::GetRenderingPosZ() const
{
	return occupiedField->GetY() - (occupiedField->GetBoard()->PlayableHeight() + 1) / 2.0f;
}

void Unit::UpdateRenderingObjectPosition() const
{
	renderingObject->position = vec3(GetRenderingPosX(), 0.0f, GetRenderingPosZ());
}

void Unit::SetCustomRenderingObjectPosition(float x, float z, float up) const
{
	renderingObject->position = vec3(x, up, z);
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
}

void Unit::UpdateInfoBar(mat4 perspective, mat4 view, int winWidth, int winHeight) const
{
	auto homopos = perspective * view * vec4(GetRenderingPosX(), 1.2f, GetRenderingPosZ(), 1.0f);
	auto posvec = vec3(homopos.x / homopos.w, homopos.y / homopos.w, homopos.z / homopos.w);
	auto posX = ((posvec.x + 1) / 2.0f) * winWidth - 60;
	auto posY = ((1 - posvec.y) / 2.0f) * winHeight - 19;
	auto depth = 1 - posvec.z;

	QVariant returnedValue;
	if (posvec.z < 0 || posvec.z > 1)
	{
		QMetaObject::invokeMethod(infoBar, "hide",
			Q_RETURN_ARG(QVariant, returnedValue));
	}
	else
	{
		QMetaObject::invokeMethod(infoBar, "update",
			Q_RETURN_ARG(QVariant, returnedValue),
			Q_ARG(QVariant, posX),
			Q_ARG(QVariant, posY),
			Q_ARG(QVariant, depth),
			Q_ARG(QVariant, currentHP),
			Q_ARG(QVariant, maximumHP),
			Q_ARG(QVariant, currentEN),
			Q_ARG(QVariant, maximumEN)
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
}

void Unit::Unselect() const
{
	renderingObject->Unselect();
	QVariant returnedValue;
	QMetaObject::invokeMethod(abilitiesBar, "hide",
		Q_RETURN_ARG(QVariant, returnedValue));
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

	if(newSelectedAbility->CanAfford(this))
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
		SendToConsole(newSelectedAbility->GetName() +  " : Not enough EN (or HP) to use this ability.");
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
		SendToConsole(selectedAbility->GetName() + "This unit is STUNNED and cannot take any action.");
		return false;
	}
	movedThisTurn = true;
	return abilities[selectedAbilitySlot - 1]->Effect(GetBoard(), this, target);
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


int Unit::TakeDamage(int damageNormal, int damageEN, int damageHP)
{
	auto dealtToEN = 0;
	auto dealtToHP = 0;

	damageNormal -= damageReduction;
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

void Unit::OnTurnBegin()
{
	movedThisTurn = false;
	regenerate();
}

void Unit::OnTurnEnd()
{
	if (restless)
	{
		if (restlessDuration <= 0)
		{
			restless = false;
		}
		else
		{
			restlessDuration--;
		}

		// this is inside the restless if because stunned units are also restless
		if (stunned)
		{
			if (stunDuration <= 0)
			{
				stunned = false;
			}
			else
			{
				stunDuration--;
			}
		}
	}

	if (!movedThisTurn)
	{
		rest();
	}
}




