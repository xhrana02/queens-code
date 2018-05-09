//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "GameEnums.h"

class AiConfiguration
{
	void setCommonValues();
	void setEasyValues();
	void setNormalValues();
	void setHardValues();
public:
	// Moves manager values
	int gen1MaxMoves;
	int gen2MaxMoves;

	// Rewards
	long victoryVal;
	long unitVal;
	long enVal;
	long hpVal;

	// Penalties
	long stunnedPen;
	long restlessPen;
	long dangerPen;
	long throneDistancePen;
	long claustrophobiaPen;
	long lonelinessPen;

	// Multipliers
	float royaltyMul;
	float agressivityMul;
	float multipleTargetsMul;
	float threatCanHurtMul;
	float threatCantHurtMul;


	explicit AiConfiguration(AiType type);
};
