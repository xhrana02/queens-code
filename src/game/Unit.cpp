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

using namespace std;
using namespace fsg;
using namespace glm;

/**
* \brief Rendering position X (in both rendering and game coords).
*/
float Unit::GetRenderingPosX() const
{
	return occupiedField->GetX() - (occupiedField->GetBoard()->PlayableWidth() + 1) / 2.0f;
}

/**
 * \brief Rendering position Z (in rendering coords, Y in game coords).
 */
float Unit::GetRenderingPosZ() const
{
	return occupiedField->GetY() - (occupiedField->GetBoard()->PlayableHeight() + 1) / 2.0f;
}

Unit::~Unit()
{
	infoBar->deleteLater();
	abilitiesBar->deleteLater();
}

void Unit::UpdateRenderingObjectPosition() const
{
	renderingObject->position = vec3(GetRenderingPosX(), 0.0f, GetRenderingPosZ());
}

void Unit::SetCustomRenderingObjectPosition(float x, float z, float up) const
{
	renderingObject->position = vec3(x, up, z);
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
			Q_ARG(QVariant, currentHitPoints),
			Q_ARG(QVariant, GetMaximumHitPoints()),
			Q_ARG(QVariant, currentEnergy),
			Q_ARG(QVariant, GetMaximumEnergy())
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

void Unit::Select()
{
	renderingObject->Select();
	QVariant returnedValue;
	QMetaObject::invokeMethod(abilitiesBar, "show",
		Q_RETURN_ARG(QVariant, returnedValue));
}

void Unit::Unselect()
{
	renderingObject->Unselect();
	QVariant returnedValue;
	QMetaObject::invokeMethod(abilitiesBar, "unselectAll",
		Q_RETURN_ARG(QVariant, returnedValue));
	QMetaObject::invokeMethod(abilitiesBar, "hide",
		Q_RETURN_ARG(QVariant, returnedValue));
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

int Unit::ReduceHP(int amount)
{
	if(amount <= 0)
	{
		return 0;
	}

	if(amount > GetCurrentHitPoints())
	{
		amount = currentHitPoints;
	}

	currentHitPoints -= amount;

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
		amount = currentEnergy;
	}

	currentEnergy -= amount;

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




