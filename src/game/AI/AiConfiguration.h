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

	// Positive values
	long victoryVal;
	long unitVal;
	long enVal;
	long hpVal;
	long buffVal;

	// Negative values
	long stunnedVal;
	long restlessVal;
	long throneProximityVal;
	long claustrophobiaVal;

	// Multipliers
	float royaltyMul;
	float agressivityMul;
	float multipleTargetsMul;


	explicit AiConfiguration(AiType type);
};
