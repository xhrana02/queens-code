//----------------------------------------------//
//	Author: Pavel Hranáč (xhrana02)				//
//	School: Vysoké učení technické v Brně		//
//	Faculty: Fakulta informačních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Player.h"

/**
 * \brief Player constructor.
 * \param name Player name.
 * \param code Player code.
 */
Player::Player(QString name, int code)
{
	_name = name;
	DecodePlayerType(code);
}


/**
 * \brief Decodes player's type from a code.
 * \param code Player's type encoded as integer.
 */
void Player::DecodePlayerType(int code)
{
	auto lastDigit = code % 10;
	if (lastDigit > 0){
		_playerType = AI;
		switch(lastDigit)
		{
		case 1:
			_aiType = Easy;
			return;
		case 2:
			_aiType = Normal;
			return;
		case 3:
			_aiType = Hard;
			return;
		case 4:
			_aiType = Custom;
			return;
		default: 
			throw std::exception(
				"Player.DecodePlayerType: Invalid player code.");
		}
	}

	_playerType = Human;
	_aiType = None;
}
