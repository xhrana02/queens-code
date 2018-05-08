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
	// Positive values
	victoryVal = 1000000;
	unitVal = 1000;
	enVal = 750;
	hpVal = 1000;
	buffVal = 150;

	// Negative values
	stunnedVal = -250;
	restlessVal = -150;
	throneProximityVal = -35; // per tile
	claustrophobiaVal = -150;

}

void AiConfiguration::setEasyValues()
{
	// Moves manager values
	gen1MaxMoves = 3;
	gen2MaxMoves = 1;

	// Multipliers
	royaltyMul = 5.0f;
	agressivityMul = 2.0f;
	multipleTargetsMul = 0.15f;
}

void AiConfiguration::setNormalValues()
{
	// Moves manager values
	gen1MaxMoves = 5;
	gen2MaxMoves = 2;

	// Multipliers
	royaltyMul = 7.5f;
	agressivityMul = 1.7f;
	multipleTargetsMul = 0.2f;
}

void AiConfiguration::setHardValues()
{
	// Moves manager values
	gen1MaxMoves = 10;
	gen2MaxMoves = 3;

	// Multipliers
	royaltyMul = 10.0f;
	agressivityMul = 1.4f;
	multipleTargetsMul = 0.25f;
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
