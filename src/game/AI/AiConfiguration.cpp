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
	unitVal = 4000;
	enVal = 700;
	hpVal = 1000;

	// Penalties
	stunnedPen = -250;
	restlessPen = -150;
	throneDistancePen = -10;
	claustrophobiaPen = -30;

	// Multipliers
	multipleTargetsMul = 0.2f;
	threatCanHurtMul = 0.02f;
	threatCantHurtMul = 0.01f;

}

void AiConfiguration::setEasyValues()
{
	// Moves manager values
	gen1MaxMoves = 3;
	gen2MaxMoves = 1;

	// Penalties
	dangerPen = -11;
	lonelinessPen = -3;

	// Multipliers
	royaltyMul = 15.0f;
	agressivityMul = 1.75f;
}

void AiConfiguration::setNormalValues()
{
	// Moves manager values
	gen1MaxMoves = 4;
	gen2MaxMoves = 2;

	// Penalties
	dangerPen = -13;
	lonelinessPen = -4;

	// Multipliers
	royaltyMul = 20.0f;
	agressivityMul = 1.5f;
}

void AiConfiguration::setHardValues()
{
	// Moves manager values
	gen1MaxMoves = 5;
	gen2MaxMoves = 3;

	// Penalties
	dangerPen = -15;
	lonelinessPen = -5;

	// Multipliers
	royaltyMul = 25.0f;
	agressivityMul = 1.25f;
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
