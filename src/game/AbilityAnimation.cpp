//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
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
