//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Player.h"

using namespace std;
using namespace fsg;

Player::~Player()
{
	for (auto unit : units)
	{
		delete unit;
	}
}

/**
 * \brief Player constructor.
 * \param inName Player inName.
 * \param inCode Player inCode.
 */
Player::Player(QString inName, int inCode)
{
	name = inName;
	DecodePlayerType(inCode);
}

/**
 * \brief Decodes player's type from a code.
 * \param code Player's type encoded as integer.
 */
void Player::DecodePlayerType(int code)
{
	auto lastDigit = code % 10;
	if (lastDigit > 0){
		playerType = AI;
		switch(lastDigit)
		{
		case 1:
			aiType = Easy;
			return;
		case 2:
			aiType = Normal;
			return;
		case 3:
			aiType = Hard;
			return;
		case 4:
			aiType = Custom;
			return;
		default: 
			throw exception("Player.DecodePlayerType: Invalid player code.");
		}
	}

	playerType = Human;
	aiType = None;
}
