//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "SpecialDemonShield.h"
#include "Game.h"
#include "Field.h"
#include "Flash.h"
#include "Targetfinding.h"
#include "DemonShield.h"
#include "CommonTooltips.h"

using namespace glm;

SpecialDemonShield::SpecialDemonShield()
{
    costHP = 2;
    costEN = 2;
    name = "Demon Shield";
    iconPath = "icons/SpecialDemonShield.png";
    description = "<b><u>Demon Shield</u> ( 2 HP, 2 EN ) Indirect 0-3</b><br><br>"
        "The targeted ally gains 6 Armor for the next 2 turns.<br>"
        ARMOR_TOOLTIP;
	aiTargetValue = 15;
	aiTargetMissingHpMod = 0.7f;
	aiTargetMissingEnMod = 0.3f;
	aiTargetRelativeEnMod = 0.0f;
}

bool SpecialDemonShield::Effect(Board* board, Unit* abilityUser, Field* target)
{
    if(CanUse(board, abilityUser, target))
    {
        abilityUser->ReduceEN(costEN);
        abilityUser->ReduceHP(costHP);
		auto targetUnit = target->GetUnitOnField();
        targetUnit->ApplyBuff(new DemonShield(targetUnit));

        if(game->IsRealGame())
        {
            game->PanCameraToField(target);
            // ReSharper disable once CppNonReclaimedResourceAcquisition
            new Flash(game, target->GetUnitOnField(), vec4(0.5f, 0.2f, 0.1f, 0.9f), 20, 15);
        }
        return true;
    }
    return false;
}

void SpecialDemonShield::OnSelected(Board* board, Unit* abilityUser)
{
    board->HalflightFields(Targetfinding::GetIndirectAllyTargets(board, abilityUser, rangeMin, rangeMax, true));
}

void SpecialDemonShield::SelectedAbilityOnFieldHovered(Board* board, Unit* abilityUser, Field* hoveredField)
{
    board->HighlightField(hoveredField);
    if(CanUse(board, abilityUser, hoveredField))
    {
        abilityUser->ReduceTheoreticalEN(costEN);
        abilityUser->ReduceTheoreticalHP(costHP);
    }
}

void SpecialDemonShield::calculateViableTargets(Board* board, Unit* abilityUser)
{
	viableTargets = Targetfinding::GetIndirectAllyTargets(board, abilityUser, rangeMin, rangeMax);
}
