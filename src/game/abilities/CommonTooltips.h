//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#define REGENERATION_TOOLTIP "<i>Each unit Regenerates at the start of its owner's turn, regaining 3 EN .</i>"
#define REST_TOOLTIP "<i>Units that have not taken any action during the turn Rest, regaining 1 HP and 3 EN.</i>"
#define MOVEMENT_TOOLTIP "<i>Diagonal pathing is possible if both neighbouring perpendicular tiles are also empty.</i>"
#define NORMAL_DAMAGE_TOOLTIP "<i>Normal damage first reduces EN before it can reduce HP.</i>"
#define HP_DAMAGE_TOOLTIP "<i>HP damage directly reduces target's HP. This is the most powerful form of damage.</i>"
#define EN_DAMAGE_TOOLTIP "<i>EN damage can only reduce target's EN.</i>"
#define COMBINED_DAMAGE_TOOLTIP "<i>HP damage is dealt first, EN damage second, and normal damage last.</i>"
#define ARMOR_TOOLTIP "<i>Units with Armor take 1 damage less for each point of Armor.</i>"
#define STUN_TOOLTIP "<i>Stunned units can't take actions and are Restless.</i>"
#define RESTLESS_TOOLTIP "<i>Restless units can't rest.</i>"