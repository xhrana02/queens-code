#pragma once
#include "Ability.h"

class PassiveAbility : public Ability
{
public:
    PassiveAbility()
    {
        isPassive = true;
    }

    bool Effect(Board* board, Unit* abilityUser, Field* target) final
    {
		// IS PASSIVE, always does nothing
        return false;
    }

	bool CanAfford(Unit* abilityUser) const final
	{
		// IS PASSIVE, always does nothing
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

    void SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField) final
    {
        // IS PASSIVE, always does nothing
    }

protected:
	void calculateViableTargets(Board* board, Unit* abilityUser) final
	{
		// IS PASSIVE, always does nothing
	}
};
