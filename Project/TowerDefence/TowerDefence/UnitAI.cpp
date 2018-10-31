#include "UnitAI.h"
#include "Cell.h"


UnitAI::UnitAI(){

}


/*
Input:
	u: The Unit the AI instance is going to control.
Function:
	Constructor
*/
UnitAI::UnitAI(Unit* u) {
	unit = u;

}

/*
Function:
	Return the Unit under the AIs control.
*/
Unit* UnitAI::get_unit() {
	return unit;
}

void UnitAI::tower_action(Cell*** lane) {

}

void UnitAI::soldier_action(Cell*** lane) {

}

/*
Function: 
	Constructor for the empty AI.
	Empty AI is the default object in a Cell. 
*/
EmptyAI::EmptyAI(Unit* u) :UnitAI(u) {

}

/*
Function:
	Default Constructor for the Example Tower AI of A.
*/
TowerAIA::TowerAIA(): UnitAI() {

}

/*
Function:
	Constructor for the Example Tower AI of A.
*/
TowerAIA::TowerAIA(Unit* u) : UnitAI(u) {

}


/*
Input:
	The lane on which this tower is build. Representing its field of vision and holding all the Objects it can act upon.
Function:
	Example Tower AI of player A. Default toweraction for all Towers. Replace this with your own Toweraction Function.
	The Tower will check every Cell in its range and attack the first enemy it finds.
*/
void TowerAIA::tower_action(Cell*** lane) {
	int range = get_unit()->get_range();

	for (int yRange = -range; yRange <= range;yRange++){
		for (int xRange = -range; xRange <= range; xRange++) {
			int nextY = yRange + unit->get_position()->get_Y();
			int nextX = xRange + unit->get_position()->get_X();
			if (nextX>= 0 && nextX < WIDTH && nextY >= 0 && nextY < HIGHT) {
				vector<Unit*> enemies = lane[yRange + unit->get_position()->get_Y()][xRange + unit->get_position()->get_X()]->get_enemies(unit->get_owner());
				if (!enemies.empty()) {
					unit->attack_unit(enemies.back());
					return;
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoldierAIA::SoldierAIA() : UnitAI() {

}

SoldierAIA::SoldierAIA(Unit* u) : UnitAI(u) {

}

/*
Input:
	The lane on which this Soldier is deployed. Representing its field of vision and holding all the Objects it can act upon.
Function:
	Example Soldier AI of player A. Default action for all Towers. Replace this with your own soldier_action Function.
	The unit will score if it has reached the last line of the lane.
	if it can walk it will otherwise it will attack the tower in its way.
*/
void SoldierAIA::soldier_action(Cell*** lane) {
	if (unit->get_position()->get_Y() == 0) {
		unit->score();
	}
	else
	{
		if (lane[unit->get_position()->get_Y()-1][unit->get_position()->get_X()]->is_blocked()) {
			unit->attack_unit(lane[unit->get_position()->get_Y()-1][unit->get_position()->get_X()]->get_enemies(unit->get_owner()).front());
		}
		else
		{
			unit->move_to(lane[unit->get_position()->get_Y() - 1][unit->get_position()->get_X()]);
		}
	}
}


MissileAIA::MissileAIA(Unit* u) : TowerAIA(u) {

}

RocketAIA::RocketAIA(Unit* u) : TowerAIA(u) {

}

FrostAIA::FrostAIA(Unit* u) : TowerAIA(u) {

}

BlockadeAIA::BlockadeAIA(Unit* u) : TowerAIA(u) {

}



ShieldAIA::ShieldAIA(Unit* u) : SoldierAIA(u) {

}

RifleAIA::RifleAIA(Unit* u) : SoldierAIA(u) {

}

BombAIA:: BombAIA(Unit* u) : SoldierAIA(u) {

}

HorseAIA::HorseAIA(Unit* u) : SoldierAIA(u) {

}

/*
Input:
The lane on which this Soldier is deployed. Representing its field of vision and holding all the Objects it can act upon.
Function:
Example Soldier AI of player A. Default action for all Towers. Replace this with your own soldier_action Function.
The unit will score if it has reached the last line of the lane.
If it can walk it will as far as possible with its speed of 2. Otherwise it will attack the tower in its way.
*/
void HorseAIA::soldier_action(Cell*** lane) {
	if (unit->get_position()->get_Y() == 0) {
		unit->score();
	}
	else
	{
		if (unit->get_position()->get_Y() >= 2) {
			if (lane[unit->get_position()->get_Y() - 2][unit->get_position()->get_X()]->is_blocked()) {
				if (lane[unit->get_position()->get_Y() - 1][unit->get_position()->get_X()]->is_blocked()) {
					unit->attack_unit(lane[unit->get_position()->get_Y() - 1][unit->get_position()->get_X()]->get_enemies(unit->get_owner()).front());
				}
				else {
					unit->move_to(lane[unit->get_position()->get_Y() - 1][unit->get_position()->get_X()]);
				}
			}
			else
			{
				unit->move_to(lane[unit->get_position()->get_Y() - 2][unit->get_position()->get_X()]);
			}
		}
		else {
			if (lane[unit->get_position()->get_Y() - 1][unit->get_position()->get_X()]->is_blocked()) {
				unit->attack_unit(lane[unit->get_position()->get_Y() - 1][unit->get_position()->get_X()]->get_enemies(unit->get_owner()).front());
			}
			else
			{
				unit->move_to(lane[unit->get_position()->get_Y() - 1][unit->get_position()->get_X()]);
			}
		}
		
	}
}