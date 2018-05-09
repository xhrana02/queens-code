//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "AiConfiguration.h"
#include <exception>


void AiConfiguration::setCommonValues()
{
	// Rewards
	victoryVal = 1000000;
	unitVal = 3000;
	enVal = 700;
	hpVal = 1000;

	// Penalties
	stunnedPen = -250;
	restlessPen = -150;
	dangerPen = -15;
	throneDistancePen = -10;
	claustrophobiaPen = -30;
	lonelinessPen = -5;

	// Multipliers
	multipleTargetsMul = 0.2f;
	threatCanHurtMul = 0.02f;
	threatCantHurtMul = 0.01f;

}

void AiConfiguration::setEasyValues()
{
	// Moves manager values
	gen1MaxMoves = 5;
	gen2MaxMoves = 2;

	// Multipliers
	royaltyMul = 10.0f;
	agressivityMul = 1.2f;
}

void AiConfiguration::setNormalValues()
{
	// Moves manager values
	gen1MaxMoves = 7;
	gen2MaxMoves = 2;

	// Multipliers
	royaltyMul = 15.0f;
	agressivityMul = 1.4f;
}

void AiConfiguration::setHardValues()
{
	// Moves manager values
	gen1MaxMoves = 10;
	gen2MaxMoves = 2;

	// Multipliers
	royaltyMul = 20.0f;
	agressivityMul = 1.6f;
}

AiConfiguration::AiConfiguration(AiType type)
{
	setCommonValues();
	switch(type)
	{
	case Easy:
		setEasyValues();
		break;
	case Normal:
		setNormalValues();
		break;
	case Hard:
		setHardValues();
		break;
	default:
		throw std::exception("AiConfiguration::AiConfiguration - Invalid AI type.");
	}
}
