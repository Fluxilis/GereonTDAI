#include "Commander.h"

const int DEPLENGTH = 100;


/*
Input:
	i : id as either player 1 or 2
	w: width of the lane
	h: hight of the lane
Function:
	Constructor
	money:	int representation of currency to by units.
	initializes hight without the topmost line so the players don*t build there.*/
Commander::Commander(int i, int w, int h){
	id = i;
	width = w;
	hight = h-1;
	money = 100;
}

/*
Input:
	int representation of currency to by units
Function:
	Adds new funds to existing money*/
void Commander::recieve_funds(int fund) {
	money += fund;
}

/*
Default build turret function.
Does nothing.*/
void Commander::build_turrets(Cell*** &lane) {
	vector<UnitAI*> toBeBuild;

}
/*
Input:
	unit that needs to be paid for.
Function:
	checks if the player has enough funds to build this unit.
	If he does the money for the Unit is subtracted from his funds and the unit is added to the army.
Return:
	True if Unit was successfully paid for.
*/
bool Commander::salary_paid(UnitAI* u) {
	
	if (money >= *u->get_unit()->get_cost()) {
		army.push_back(u);
		return true;
	}
	
	return false;
}

/*
Function:
	Get function for all towers build.
Return:
	Returns all Towers of this player.*/
vector<UnitAI*>* Commander::get_towers() {
	return &towers;
}

/*
Function:
Get function for all soldiers in the army.
Return:
Returns all Towers of this player.*/
vector<UnitAI*>* Commander::get_soldiers() {
	return &army;
}

/*
Function:
	showes if this is player 1 or 2.
*/
int Commander::get_id() {
	return id;
}

/*
Function:
	Checks if towers were destroyed.
	They are removed and their value is returned to be added to the enemy funds.
Return:
	the sum of all values of destroyed towers to be added to enemy funds.
*/
int Commander::update_towers() {
	int funds = 0;
	for (vector<UnitAI*>::iterator it = towers.begin(); it != towers.end();) {
		if ((*it)->get_unit()->get_health() <= 0) {
			
			Unit* tbr = (*it)->get_unit();
			funds += *(*it)->get_unit()->get_cost();
			(*it)->get_unit()->get_position()->remove_tower(*tbr);
			it = towers.erase(it);

		}
		else {
			(*it)->get_unit()->activate();
			it++;
		}
		
	}
	return funds;
}

void Commander::recrute_soldiers() {}


/*
Function:
	Deployment function that sends out soldiers in a predetermined manner.
	Overload to your linking.
Returns:
Needs to return a vector of Deployment structs. The struct can be found in Commander.h
*/
vector<Depoyment*>* Commander::deploy() {

	vector<Depoyment*>* deploymentList = new vector<Depoyment*>;

	for (int h = 0; h < DEPLENGTH; h++) {
		deploymentList[h] = vector<Depoyment*>();
		bool notset = true;
		for (int w = 0; w < width; w++) {
			if (notset && h == w && h < army.size()) {
				deploymentList[h].push_back(new Depoyment);
				deploymentList[h].back()->pos = w;
				deploymentList[h].back()->wave = h;
				deploymentList[h].back()->unit = new UnitAI;
			}

		}
	}
	return deploymentList;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Change A CommaderA or B to whatever name you like
Then Change their Functions and in order to implement your AI
In Unit AI create a new version of UnitAIA with corresponding names.
When recruiting solders or building towers use your UnitAIX version.

*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CommanderA::CommanderA(int i, int w, int h): Commander(i, w, h) {
	switchi = 0;

}

void CommanderA::build_turrets(Cell*** &lane) {
	vector<UnitAI*> toBeBuild;


	Unit *u ;
	UnitAI* ai ;
	if (switchi %2 == 0)
	{
		u = new MissileTower(id);
		ai = new MissileAIA(u);

	}
	else {
		u = new Blockade(id);
		ai = new BlockadeAIA(u);
	}
	switchi++;
	if (u->place_tower(lane[0][(switchi%7)-1], &money)) {
		towers.push_back(ai);
	}


}

void CommanderA::recrute_soldiers() {

	Unit *u = new RifleSoldier(id);
	UnitAI* ai = new RifleAIA(u);
	army.push_back(ai);

	



}

vector<Depoyment*>* CommanderA::deploy() {
	vector<Depoyment*>* deploymentList = new vector<Depoyment*>[DEPLENGTH];

	for (int h = 0; h < DEPLENGTH; h++) {
		deploymentList[h] = vector<Depoyment*>();
		if (h <army.size()) {
			deploymentList[h].push_back(new Depoyment);
			deploymentList[h].back()->pos = h;
			deploymentList[h].back()->wave = h;
			deploymentList[h].back()->unit = army[h];
		}

	}
	return deploymentList;
}

vector<UnitAI*>* CommanderA::get_towers() {
	return &towers;
}

vector<UnitAI*>* CommanderA::get_soldiers() {
	return &army;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CommanderB::CommanderB(int i, int w, int h) : Commander(i, w, h) {


}

void CommanderB::build_turrets(Cell*** &lane) {
	vector<UnitAI*> toBeBuild;


	Unit *u = new RocketTower(id);
	UnitAI* ai = new RocketAIA(u);

	if (u->place_tower(lane[0][counter], &money)) {
		towers.push_back(ai);
		counter++;
	}

	
}



 void CommanderB::recrute_soldiers() {

	Unit *u = new HorseSoldier(id);
	UnitAI* ai = new HorseAIA(u);
	salary_paid(ai);
	Unit *u2 = new BombSoldier(id);
	UnitAI* ai2 = new BombAIA(u2);
	salary_paid(ai2);
	counter = 0;
	


}

 vector<Depoyment*>* CommanderB::deploy() {
	vector<Depoyment*>* deploymentList = new vector<Depoyment*>[DEPLENGTH];
	for (int h = 0; h < DEPLENGTH; h++) {
		deploymentList[h] = vector<Depoyment*>();
		if (h <army.size()) {
				deploymentList[h].push_back(new Depoyment);
				deploymentList[h].back()->pos = (h%width);
				deploymentList[h].back()->wave = h;
				deploymentList[h].back()->unit = army[h];
		}
	}
	return deploymentList;

}

vector<UnitAI*>* CommanderB::get_towers() {
	return &towers;
}

vector<UnitAI*>* CommanderB::get_soldiers() {
	return &army;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////

CommanderPassive::CommanderPassive(int i, int w, int h) : Commander(i, w, h) {
	switchi = 0;

}