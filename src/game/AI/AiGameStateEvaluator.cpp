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

long AiGameStateEvaluator::EvaluateGameState(AiGame* game)
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

	ResetDangerFactors(evalPlayer, enemyPlayer);
	CalculateSnowballFactor(evalPlayer, enemyPlayer);

	// EVAL PLAYER UNITS ACTIVE
	CalculateUnitsCenter(evalPlayer, game->GetGameBoard());
	for (auto unit : evalPlayer->GetUnits())
	{
		score += EvaluateUnitActiveValue(unit) * config->agressivityMul * snowballFactor;
	}
	// ENEMY PLAYER UNITS ACTIVE
	CalculateUnitsCenter(enemyPlayer, game->GetGameBoard());
	for (auto unit : enemyPlayer->GetUnits())
	{
		score -= EvaluateUnitActiveValue(unit);
	}
	
	// EVAL PLAYER UNITS STATIC
	for (auto unit : evalPlayer->GetUnits())
	{
		score += EvaluateUnitStaticValue(unit);
	}
	// ENEMY PLAYER UNITS STATIC
	for (auto unit : enemyPlayer->GetUnits())
	{
		score -= EvaluateUnitStaticValue(unit) * config->agressivityMul * snowballFactor;
	}

	return score;
}

/**
 * \brief Calculates an integer score describing how well is the given unit doing.
 * 
 * Unit is evaluated based on many different factors including:
 * HP, EN, danger, claustrophobia, status effects
 */
long AiGameStateEvaluator::EvaluateUnitStaticValue(Unit* unit) const
{
	////////// ROYALTY RELEVANT SCORE //////////
	long unitScore = config->unitVal;
	auto hpPotential = unit->GetCurrentHitPoints() + unit->GetRegenerationHP();
	auto enPotential = unit->GetCurrentEnergy() + unit->GetRegenerationEN();

	if (unit->IsRestless())
	{
		// Restless on units with low HP has more value 
		unitScore += (unit->GetMissingHP() + 0.1f) * unit->GetRestlessDuration() * config->restlessPen;
	}
	else if (unit->MovedThisTurn())
	{
		unitScore += (unit->GetMissingHP() + 0.1f) * config->restlessPen;
	}
	else
	{
		hpPotential += unit->GetRestHP();
		enPotential += unit->GetRestEN();
	}

	auto hpValue = float(hpPotential) / unit->GetMaximumHitPoints();
	if (hpValue > 1.0f) { hpValue = 1.0f; }
	auto enValue = float(enPotential) / unit->GetMaximumHitPoints();
	if (enValue > 1.0f) { enValue = 1.0f; }
	unitScore += hpValue * config->hpVal;
	unitScore += enValue * config->enVal;

	// twice the danger, four times the problem | low HP/EN units in danger is a bigger problem than full HP/EN units in danger
	unitScore += pow(unit->DangerFactor, 3) * (3 - hpValue - enValue) * config->dangerPen;

	if (unit->IsRoyalty)
	{
		unitScore *= config->royaltyMul;
	}

	////////// ROYALTY IRRELEVANT SCORE //////////
	if (unit->IsStunned())
	{
		// Stun on units with high EN has more value 
		unitScore += (1.1f - unit->GetMissingEN()) * unit->GetStunDuration() * config->stunnedPen;
	}
	auto claustrophobia = 3 - unit->NumberOfEmptyNeighbors();
	if (claustrophobia < 0) { claustrophobia = 0; }
	unitScore += claustrophobia * config->claustrophobiaPen;

	return unitScore;
}

/**
* \brief Calculates an integer score describing her capabilities.
* 
* Unit is evaluated based on many different factors including:
* viable targets, throne proximity, loneliness
*/
long AiGameStateEvaluator::EvaluateUnitActiveValue(Unit* unit) const
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
			// skip unimportant abilities like movement for better performance
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
				if (targetUnit->IsRoyalty && targetUnit->IsEnemy(unit) && ability->GetAiCanHurt())
				{
					targetScore *= config->royaltyMul;
				}
			}
			if (targetUnit->IsEnemy(unit))
			{
				float danger = targetScore;
				if (ability->GetAiCanHurt())
				{
					danger -= targetUnit->GetArmor() * 5;
					danger *= config->threatCanHurtMul;
				}
				else
				{
					danger *= config->threatCantHurtMul;
				}

				if (danger > 0.0f)
				{
					targetUnit->DangerFactor += danger;
				}
			}
			targetScoresTotal += targetScore;
		}
		unitScore += ceil(targetScoresTotal);
	}

	auto toughness = GetUnitToughness(unit);
	if (unit->GetBoard()->GetThroneField())
	{
		unitScore += GetYDeltaFactor(unit->GetOccupiedField(), unit->GetBoard()->GetThroneField()) * config->throneDistancePen * toughness;
	}

	if (unit->IsRoyalty)
	{
		unitScore += GetDistanceFactor(unit->GetOccupiedField(), playerUnitsCenter) * config->lonelinessPen * config->royaltyMul;
	}
	else
	{
		unitScore += GetDistanceFactor(unit->GetOccupiedField(), playerUnitsCenter) * config->lonelinessPen / toughness;
	}

	return unitScore;
}

int AiGameStateEvaluator::GetDistanceFactor(Field* from, Field* to)
{
	auto deltaX = from->GetX() - to->GetX();
	auto deltaY = from->GetY() - to->GetY();
	return pow(deltaX, 2) + pow(deltaY, 2);
}

int AiGameStateEvaluator::GetYDeltaFactor(Field* from, Field* to)
{
	auto deltaY = from->GetY() - to->GetY();
	return pow(deltaY, 2);
}

void AiGameStateEvaluator::CalculateUnitsCenter(Player* player, Board* board)
{
	auto unitsXcumulative = 0;
	auto unitsYcumulative = 0;
	auto unitsCount = 0;
	for (auto unit : player->GetUnits())
	{
		unitsXcumulative += unit->GetOccupiedField()->GetX();
		unitsYcumulative += unit->GetOccupiedField()->GetY();
		unitsCount++;
	}
	playerUnitsCenter = board->GetField(
		round(float(unitsXcumulative) / unitsCount), round(float(unitsYcumulative) / unitsCount));
}

void AiGameStateEvaluator::CalculateSnowballFactor(Player* evalPlayer, Player* enemyPlayer)
{
	snowballFactor = 1 + (evalPlayer->GetUnits().size() - enemyPlayer->GetUnits().size()) * 0.2f;
	if (snowballFactor < 0.3f) { snowballFactor = 0.3f; }
	if (snowballFactor > 2.0f) { snowballFactor = 2.0f; }
}

void AiGameStateEvaluator::ResetDangerFactors(Player* evalPlayer, Player* enemyPlayer)
{
	for (auto unit : evalPlayer->GetUnits())
	{
		unit->DangerFactor = 0;
	}
	for (auto unit : enemyPlayer->GetUnits())
	{
		unit->DangerFactor = 0;
	}
}

float AiGameStateEvaluator::GetUnitToughness(Unit* unit)
{
	return pow(unit->GetCurrentHitPoints() * 0.07f + unit->GetCurrentEnergy() * 0.04f + unit->GetArmor() * 0.1f, 2);
}
