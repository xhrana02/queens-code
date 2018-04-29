#pragma once
#include "Ability.h"

class PassiveAbility : public Ability
{
public:
	PassiveAbility()
	{
		isPassive = true;
	}

	bool Effect(Board* board, Unit* abilityUser, Field* target) override
	{
		// Can be overriden in some passive abilities (like Opportunity Attack)
		return false;
	}

	bool CanUse(Board* board, Unit* abilityUser, Field* target) final
	{
		// IS PASSIVE, always does nothing
		return false;
	}

	void OnSelected(Board* board, Unit* abilityUser) final
	{
		// IS PASSIVE, always does nothing
	}

	void SelectedAbilityOnFieldHovered(Board* board, Field* hoveredField) final
	{
		// IS PASSIVE, always does nothing
	}
};
