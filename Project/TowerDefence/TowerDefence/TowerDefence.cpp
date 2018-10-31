#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include "TowerDefence.h"
#include "Commander.h"
#include "Unit.h"
#include "UnitAI.h"
using namespace std;

const int WIDTH = 7;
const int HIGHT = 20;


/*
Input:
	lane1: lane of player 1
	lane2: lane of player 2
Function:
	prints the lanes of both players. 
	Every Cell only prints the last occupant in the list.*/

void printLanes(Cell*** lane1, Cell*** lane2)
{
	cout << "_";
	for (int cell = 0; cell < WIDTH; cell++) {
		cout << "______";
	}
	cout << "       ";
	for (int cell = 0; cell < WIDTH; cell++) {
		cout << "______";
	}
	cout << endl;

	for (int column = 0; column < HIGHT+1; column++) {
		cout << "|  ";
		for (int cell = 0; cell < WIDTH; cell++) {
			lane1[column][cell]->printCell();
		}
		cout << "     |  ";
		for (int cell = 0; cell < WIDTH; cell++) {
			lane2[column][cell]->printCell();
		}
		cout << endl;

		cout << "|";
		for (int cell = 0; cell < WIDTH; cell++) {
			cout << "_____|";
		}
		cout << "       |";
		for (int cell = 0; cell < WIDTH; cell++) {
			cout << "_____|";
		}
		cout << endl;
	}
	cout << endl << endl << endl;


}

/*
Input:
	deployment: vector of deployment structs that hold when and where a unit is deployed during this round.
	lane: lane the units are deployed in.
	army: gathering of all units that participate in this rounds attack. 
Function:
	resets all units in deployment to their starting values, sets them in position and adds them to the army.
*/
void deploy(vector<Depoyment*>* deployment, Cell*** lane, vector<UnitAI*>* army) {
	for (vector<Depoyment*>::iterator it = deployment->begin(); it != deployment->end(); ++it) {
		(*it)->unit->get_unit()->reset();
		UnitAI* s = new UnitAI();
		s = (*it)->unit;
		army->push_back(s);
		lane[HIGHT][(*it)->pos]->deploy_unit(*s->get_unit());
	}
}

/*
Input:
	army: all soldiers to be cleared
	lane: lane where all remaining soldiers most be removed. 
Function:
	removes all Soldiers from the lane and resets them.*/
void clean_army(vector<UnitAI*>* army, Cell*** lane) {
	for (vector<UnitAI*>::iterator it = army->begin(); it != army->end(); ++it) {
		int xpos = (*it)->get_unit()->get_position()->get_X();
		int ypos = (*it)->get_unit()->get_position()->get_Y();
		UnitAI* oc = (*it);
		lane[ypos][xpos]->remove_occupant(*oc->get_unit());
		(*it)->get_unit()->reset();

	}
}

/*
Input: 
	army: Units to be checked
	Commander: Enemy commander, that get rewarded for destroyed units.
	HP: Enemy HP
Function:
	Increases the enemy commanders fonds by 1+ 1 for each destroyed unit
	Reduces the enemy HP for every unit that has scored
	reactivates all units
Return:
	additional funds for the enemy commander.*/
int update_army(vector<UnitAI*>* army, Commander* commander, int* HP) {
	int funds = 1;
	for (vector<UnitAI*>::iterator it = army->begin(); it != army->end();) {
		if ((*it)->get_unit()->has_scored()){

			*HP -= 1;
		}

		if (it != army->end() && (*it)->get_unit()->get_health() <= 0) {
			Unit* tbr =(*it)->get_unit();
			funds += 1;
			(*it)->get_unit()->get_position()->remove_occupant(*tbr);
			it = army->erase(it);
			
		}
		else {
		(*it)->get_unit()->activate();
		it++;
		}
		
	}
	funds += commander->update_towers();
	return funds;
}

/*
Input:
	towers: towers that will act
	lane: lane the towers can act on.
Function:
	lets all towers perform their action of the turn.*/
void tower_action(vector<UnitAI*>* towers, Cell*** lane) {
	for (vector<UnitAI*>::iterator it = towers->begin(); it != towers->end(); ++it) {
		(*it)->tower_action(lane);
	}
}

/*
Input:
soldier: soldiers that will act
lane: lane the towers can act on.
Function:
lets all soldiers perform their action of the turn.*/
void soldier_action(vector<UnitAI*>* soldiers, Cell*** lane) {
	for (vector<UnitAI*>::iterator it = soldiers->begin(); it != soldiers->end(); ++it) {
		(*it)->soldier_action(lane);
	}
}

/*
Input:
	lane1: lane of player 1
	lane2: lane of player 2
	commander1: player 1
	commander2: player 2
	HP1 : Player 1 hp
	HP2: Player 2 hp
Function:
	Goes through the 100 timesteps of one deployment round in the following order:
		deploys all soldiers on both lanes for the current timestep:
		Lets all Towers perform their Action
		Lets all Soldiers perform their action
		Removes dead Units, updates HP and allocates new fonds to players
	At the end of a Deployment round all Soldiers are cleared
		*/
void start_attack(Cell*** lane1, Cell*** lane2, Commander* commander1, Commander* commander2, int* HP1, int* HP2) {
	vector<UnitAI*>* army1 = new vector<UnitAI*>;
	vector<UnitAI*>* army2 = new vector<UnitAI*>;
	vector<Depoyment*>* deployment1 = commander1->deploy();
	vector<Depoyment*>* deployment2 = commander2->deploy();
	for (int timestep = 0; timestep < 100; timestep++) {
		deploy(&deployment1[timestep], lane2, army1);
		deploy(&deployment2[timestep], lane1, army2);

		tower_action(commander1->get_towers(), lane1);
		tower_action(commander2->get_towers(), lane2);

		soldier_action(army1, lane2);
		soldier_action(army2, lane1);

		commander2->recieve_funds(update_army(army1, commander1, HP2));
		commander1->recieve_funds(update_army(army2, commander2, HP1));

		

		printLanes(lane1, lane2);
		cout << "Player 1 has " << *HP1 << "HP" << " left." << endl;
		cout << "Player 2 has " << *HP2 << "HP" << " left." << endl;
	}

	clean_army(army1, lane2);
	clean_army(army2, lane1);


}

/*
Input:
	lane1: Lane of player 1
	lane2: Lane of placer 2
	commander 1: player 1
	commander 2 player 2
Function:
	Sets the players HP 
	for a preset number of rounds or until a player is dead:
		let the players build towers and recruit soldiers
		perform a deployment phase*/
void update(Cell*** lane1, Cell*** lane2, Commander* commander1, Commander* commander2){
	int HP1 = 10;
	int HP2 = 10;
	int counter = 0;
	while (true) {

		commander1->build_turrets(lane1);
		commander1->recrute_soldiers();
		commander2->build_turrets(lane2);
		commander2->recrute_soldiers();

		start_attack(lane1, lane2, commander1, commander2, &HP1, &HP2);

		if (counter >= 100 || HP1 <=0 || HP2 <=0) {

			return;
		}

		counter++;

	}	
	
}

/*
Function:
	creates both players and their lanes.
	starts the game*/
int main()
{
	Cell*** lane1;
	Cell*** lane2;

	Commander *commander1 = new Commander(1, WIDTH, HIGHT);
	CommanderA commandertest1(1, WIDTH, HIGHT);
	commander1 = &commandertest1;

	Commander *commander2 = new Commander(2, WIDTH, HIGHT);
	CommanderB commandertest2(2, WIDTH, HIGHT);
	commander2 = &commandertest2;

	lane1 = new Cell**[HIGHT+1];
	lane2 = new Cell**[HIGHT+1];

	for (int h = 0; h < HIGHT+1; h++) {
		lane1[h] = new Cell*[WIDTH];
		lane2[h] = new Cell*[WIDTH];
		for (int w = 0; w < WIDTH; w++) {
			Unit *u = new Empty();
			Unit *empty_cell1 = u;
			Unit *empty_cell2 = u;
			lane1[h][w] = new Cell(*empty_cell1, w, h, lane1);
			lane2[h][w] = new Cell(*empty_cell2, w, h, lane2);
		}
	}

	update(lane1, lane2, commander1, commander2);
	
	return 0;
}