//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "AiGameStateEvaluator.h"
#include "AiGame.h"

AiGameStateEvaluator::AiGameStateEvaluator(AiType type, PlayerID inEvalPlayerID)
{
	config = std::make_unique<AiConfiguration>(type);
	evalPlayerID = inEvalPlayerID;
}

long AiGameStateEvaluator::EvaluateGameState(AiGame* game) const
{
	long score = 0;
	auto evalPlayer = game->GetPlayerByID(evalPlayerID);
	auto enemyPlayer = game->GetEnemyPlayer(evalPlayer);

	if (game->IsFinished())
	{
		if (game->wonBy == evalPlayerID)
		{
			score += config->victoryVal * config->agressivityMul;
		}
		else
		{
			score -= config->victoryVal;
		}
	}

	auto snowballFactor = 1 + (evalPlayer->GetUnits().size() - enemyPlayer->GetUnits().size()) * 0.2f;
	if (snowballFactor < 0.3f) { snowballFactor = 0.3f; }
	if (snowballFactor > 2.0f) { snowballFactor = 2.0f; }
	for (auto unit : evalPlayer->GetUnits())
	{
		score += EvaluateUnit(unit);
		score += EvaluateUnitTargets(unit) * config->agressivityMul * snowballFactor;
	}
	for (auto unit : enemyPlayer->GetUnits())
	{
		score -= EvaluateUnit(unit) * config->agressivityMul * snowballFactor;
		score -= EvaluateUnitTargets(unit);
	}

	return score;
}

long AiGameStateEvaluator::EvaluateUnit(Unit* unit) const
{
	long unitScore = config->unitVal;
	auto hpPotential = unit->GetCurrentHitPoints() + unit->GetRegenerationHP();
	auto enPotential = unit->GetCurrentEnergy() + unit->GetRegenerationEN();

	if (unit->IsStunned())
	{
		// Stun on units with high EN has more value 
		unitScore += (1 - unit->GetMissingEN()) * unit->GetStunDuration() * config->stunnedVal;
	}

	if (unit->IsRestless())
	{
		// Restless on units with low HP has more value 
		unitScore += (unit->GetMissingHP() + 1) * unit->GetRestlessDuration() * config->restlessVal;
	}
	else if (unit->MovedThisTurn())
	{
		unitScore += (unit->GetMissingHP() + 1) * config->restlessVal;
	}
	else
	{
		hpPotential += unit->GetRestHP();
		enPotential += unit->GetRestEN();
	}

	for (auto buff : unit->GetActiveBuffs())
	{
		// Buffs have more value on hurt or exhausted units
		unitScore += (0.5f + unit->GetMissingHP() + unit->GetMissingEN()) * config->buffVal;
	}

	auto hpValue = float(hpPotential) / unit->GetMaximumHitPoints();
	if (hpValue > 1.0f) { hpValue = 1.0f; }
	auto enValue = float(enPotential) / unit->GetMaximumHitPoints();
	if (enValue > 1.0f) { enValue = 1.0f; }
	unitScore += pow(hpValue, 1.5) * config->hpVal;
	unitScore += pow(enValue, 1.5) * config->enVal;

	if (unit->IsRoyalty)
	{
		unitScore *= config->royaltyMul;
	}
	else
	{
		// Royalty doesn't mind being surrounded with bodyguards
		if (!unit->CanUnitMove())
		{
			unitScore += config->claustrophobiaVal;
		}
	}
	return unitScore;
}

long AiGameStateEvaluator::EvaluateUnitTargets(Unit* unit) const
{
	long unitScore = 0;

	for (auto ability : unit->GetAbilites())
	{
		if (!ability->CanAfford(unit))
		{
			continue;
		}
		if (ability->GetAiTargetValue() < 5)
		{
			continue;
		}

		ability->CalculateViableTargets(unit->GetBoard(), unit);
		auto targets = ability->GetViableTargets();

		auto targetScoresTotal = 0.0f;
		auto firstTarget = true;
		for (auto target : targets)
		{
			if (target->IsFieldFrozen())
			{
				continue;
			}
			if (firstTarget)
			{
				targetScoresTotal = ability->GetAiTargetValue();
				firstTarget = false;
			}

			auto targetScore = ability->GetAiTargetValue();
			auto targetUnit = target->GetUnitOnField();
			if (targetUnit)
			{
				targetScore += ability->GetAiTargetValue() * (
					targetUnit->GetMissingHP() * ability->GetAiTargetMissingHpMod() +
					targetUnit->GetMissingEN() * ability->GetAiTargetMissingEnMod() + 
					targetUnit->GetRelativeEN() * ability->GetAiTargetRelativeEnMod()
				);
				if (targetUnit->IsRoyalty)
				{
					targetScore *= config->royaltyMul;
				}
			}
			targetScoresTotal += targetScore;
		}
		unitScore += ceil(targetScoresTotal);
	}

	if (unit->GetBoard()->GetThroneField())
	{
		auto throneDistance = GetDistance(unit->GetOccupiedField(), unit->GetBoard()->GetThroneField()) - 2;
		if (throneDistance < 0) { throneDistance = 0;  }
		auto distancePenalty = ceil(throneDistance * config->throneProximityVal);
		if (unit->IsRoyalty)
		{
			distancePenalty *= config->royaltyMul * 0.25f;
		}
		unitScore += distancePenalty;
	}

	return unitScore;
}

float AiGameStateEvaluator::GetDistance(Field* from, Field* to)
{
	auto deltaX = from->GetX() - to->GetX();
	auto deltaY = from->GetY() - to->GetY();
	return sqrt(float(pow(deltaX, 2) + pow(deltaY, 2)));
}
