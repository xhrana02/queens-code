//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#define REGENERATION_TOOLTIP "<br>-<i> Each unit Regenerates at the start of its owner's turn, regaining 2 EN .</i>"
#define REST_TOOLTIP "<br>-<i> Units that have not taken any action during the turn Rest, regaining 1 HP and 2 EN.</i>"
#define MOVEMENT_TOOLTIP "<br>-<i> Diagonal pathing is possible if both neighbouring perpendicular tiles are also empty.</i>"
#define NORMAL_DAMAGE_TOOLTIP "<br>-<i> Normal damage first reduces EN before it can reduce HP.</i>"
#define HP_DAMAGE_TOOLTIP "<br>-<i> HP damage reduces target's HP. This is the most powerful form of damage.</i>"
#define EN_DAMAGE_TOOLTIP "<br>-<i> EN damage can only reduce target's EN.</i>"
#define COMBINED_DAMAGE_TOOLTIP "<br>-<i> HP damage is dealt first, EN damage second, and normal damage last.</i>"
#define ARMOR_TOOLTIP "<br>-<i> Units with Armor take 1 damage less for each point of Armor. Normal damage is reduced first, EN second, HP last.</i>"
#define STUN_TOOLTIP "<br>-<i> Stunned units can't take actions and are Restless.</i>"
#define RESTLESS_TOOLTIP "<br>-<i> Restless units can't rest.</i>"
#define ACTIVEPASSIVE_TOOLTIP "<br>-<i> This ability doesn't work if this unit is Stunned.</i>"