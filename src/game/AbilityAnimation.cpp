//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "AbilityAnimation.h"
#include "Game.h"

bool AbilityAnimation::LockGame(Game* inGame)
{
    game = inGame;
    if (game != nullptr)
    {
        game->LockGame(this);
        return true;
    }
    return false;
}
