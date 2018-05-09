//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "AiUnit.h"
#include "Blessing.h"
#include "DemonShield.h"
#include "AiMove.h"
#include "Board.h"


AiUnit::AiUnit(Unit* source)
{
	name = source->GetName();
	maximumHP = source->GetMaximumHitPoints();
	currentHP = source->GetCurrentHitPoints();
	currentEN = source->GetCurrentEnergy();
	regenerationHP = source->GetRegenerationHP();
	regenerationEN = source->GetRegenerationEN();
	restHP = source->GetRestHP();
	restEN = source->GetRestEN();
	armor = source->GetArmor();
	damageModifierLine = source->GetDamageModifierLine();
	IsRoyalty = source->IsRoyalty;
	HasOpportunityAttack = source->HasOpportunityAttack;
	DamageOpportunityAttack = source->DamageOpportunityAttack;
	abilities = source->GetAbilites();
	for (auto ability : abilities)
	{
		if (ability->GetName() == "Dash")
		{
			aiHasDash = true;
		}
	}

	for (auto buff : source->GetActiveBuffs())
	{
		auto duration = buff->GetRemainingDuration();
		Buff* newBuff;
		switch (buff->GetID())
		{
		case blessing:
			newBuff = new Blessing(this);
			break;
		case demonshield:
			newBuff = new DemonShield(this);
			break;
		default:
			throw std::exception("AiUnit::AiUnit - Invalid buff ID.");
		}
		newBuff->SetRemainingDuration(duration);
		buffs.push_back(newBuff);
	}
	stunDuration = source->GetStunDuration();
	if (stunDuration > 0) { stunned = true; }
	restlessDuration = source->GetRestlessDuration();
	if (restlessDuration > 0) { restless = true; }
	movedThisTurn = source->MovedThisTurn();
}

std::vector<std::shared_ptr<AiMove>> AiUnit::GetAllPossibleMoves()
{
	auto moves = std::vector<std::shared_ptr<AiMove>>();
	if (stunned)
	{
		return moves;
	}

	auto slot = 1;
	for (auto ability : abilities)
	{
		if (!ability->CanAfford(this))
		{
			continue;
		}
		ability->CalculateViableTargets(GetBoard(), this);
		auto targets = ability->GetViableTargets();
		if (slot == 1)
		{
			for (auto target : targets)
			{
				auto newMove = std::make_shared<AiMove>(this, target, slot);
				newMove->type = MovementMove;
				newMove->costToGetHere = target->CostToGetHere;
				moves.push_back(newMove);
			}
		}
		else
		{
			for (auto target : targets)
			{
				moves.push_back(std::make_shared<AiMove>(this, target, slot));
			}
		}
		slot++;
	}
	return moves;
}

int AiUnit::NumberOfEmptyNeighbors() const
{
	if (aiHasDash)
	{
		return 4;
	}

	auto meleeFieldsFree = 0;
	for (auto field : GetBoard()->GetAllMeleeNeighborFields(GetOccupiedField()))
	{
		if (!field->IsFieldOccupied())
		{
			meleeFieldsFree++;
		}
	}
	return meleeFieldsFree;
}

float AiUnit::GetMissingHP()
{
	return (1 - float(GetCurrentHitPoints()) / GetMaximumHitPoints());
}

float AiUnit::GetMissingEN()
{
	return (1 - float(GetCurrentEnergy()) / GetMaximumHitPoints() - 0.5f);
}

float AiUnit::GetRelativeEN()
{
	return (1 - float(GetCurrentEnergy()) / GetMaximumEnergy() - 0.5f);
}
