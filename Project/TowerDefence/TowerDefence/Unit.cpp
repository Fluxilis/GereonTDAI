#include "Unit.h"
#include "Cell.h"

/*
Input: 
	integer that denotes whether its owner is player 1 or 2
Function:
	Constructor
	*/
Unit::Unit(int o = 0) {
	owner = o;
}

/*
Function:
	Virtual Deploy function of super class.
Return:
	False by default
	*/
bool Unit::deploy(Cell* c) {
	cout << "wrong instance for deploy" << endl;
	return false;
}

/*
Function:
	Virtual move_to function of super class.
*/
bool Unit::move_to(Cell* destination) {
	cout << "wrong instance for move_to" << endl;
	return false;
}

/*
Function:
	Virtual place_tower function of super class.
*/
bool Unit::place_tower(Cell* c, int* money) {
	cout << "not a tower" << endl;
	return false;
}

/*
Function:
	Virtual score function of super class.
*/
bool Unit::score() {
	cout << "wrong instance for score" << endl;
	return false;
}

/*
Function:
	get function to see if the unit has scored.
Return:
	if the Unit has scored or not.
	*/
bool Unit::has_scored() {
	return scored;
}

/*
Function:
	get function for the Units Cost.
Return:
	The cost of this Unit.
*/
int* Unit::get_cost() {
	return &cost;
}

/*
Function:
	get function for the Units position.
Return:
	Pointer to the Cell that the unit is currently assigned to.
*/
Cell* Unit::get_position() {
	return position;
}

/*
Function:
	Sets the unit to active so it can act until it's deactivated.
	*/
void Unit::activate() {
	canAct = true;
}

/*
Function:
	Deactivates Unit, so it can not act until it's reactivated.
	*/
void Unit::deactivate(){
	canAct = false;
}

/*
Function:
	Get Function for current unit HP.
Return:
	Current unit HP.
*/
int Unit::get_health(){
	return health;
}

/*
Function:
	Returns if the Unit can act.
Return:
	Boolean if the Unit can Act.
	*/
bool Unit::is_active() {
	return canAct;
}

/*
Function:
	get function for the Units Range.
Return:
	Integer symbolizing the distance to cells which inhabitants can still be attacked.
	*/
int Unit::get_range() {
	return range;
}

/*
Function:
	Resets the Unit to its initialization values.	
*/
void Unit::reset() {
	health = maxHealth;
	position = nullptr;
	scored = false;
	activate();
}

/*
Input:
	Number of HP for which this Unit has been damaged.
Function:
	Reduces the units hp by the damage it has received.*/
void Unit::damage_unit(int damage) {
	health -= damage;
}

/*
Input:
	Pointer to cell for which distance is checked.
Function:
	Checks whether a Cell is in range to be attacked by this Unit from its current position.
	*/
bool Unit::is_in_range(Cell* c) {
	return  abs(c->get_X() - position->get_X()) <= range && std::abs(c->get_Y() - position->get_Y()) <= range;
}

/*
Input:
	Pointer to Unit to be attacked.
Function:
	If the unit is in range, not deactivated or dead it damages the target.
	Deactivates Unit after action.
Return:
	Boolean weather the attack succeeded
	*/
bool Unit::attack_unit(Unit *target) {
	if (!canAct || health < 0) {
		cout << "Unit at "<< position->get_X() << " " << position->get_Y() << " can not attack because of fatigue" << endl;
		return false;
}

	if (is_in_range(target->get_position())) {
		target->damage_unit(attackStrength);
		deactivate();
		cout << "Unit at: " << position->get_X() << " " << position->get_Y() << "attacked Unit at:  " << target->get_position()->get_X() << " " << target->get_position()->get_Y() << endl ;
		return true;
	}
	
	return false;
}

/*
Input:
	signature of the Unit type as char.
Function:
	sets units signature.
*/
void Unit::set_signature(char sig) {
	signature = sig;
}

/*
Function:
	get function for signature.
Return:
	unit type signature*/
char Unit::get_signature(){
	return signature;
}

/*
Function:
	get function for unit owner.
Return:
	integer representing if the owner of the unit is player 1 or player 2.
*/
int Unit::get_owner(){
	return owner;
}

/*
Input:
	Integer showing if Owner is player 1 or player 2.
Function:
	sets Owner.
*/
void Unit::set_owner(int i) {
	owner = i;
}

/*
Function:
	Constructor of the empty unit. Used as Default inhabitant of Cells.
	*/
Empty::Empty():Unit() {
	set_signature('_');
	canAct = false;
}

/*
input: 
	Integer representing if owner is player 1 or 2
Function:
	Constructor of Tower super type units.
*/
Tower::Tower(int o): Unit(o){
	position = nullptr;
}

/*
Input:
	c: Cell on which the tower should be build.
	money: the available funds of the commander trying to build this unit.
Function:
	If the player has enough funds for this tower and the position is not blocked, constructs places tower in cell.*/
bool Tower::place_tower(Cell* c, int* money) {
	if (*money < cost) {
		cout << "Youw mama so poor she cant even build turrets" << endl;
		return false;
	}
	if (c->build_tower(*this)) {
		position = c;
		*money -= cost;
		return true;
	}
	return false;
}

/*
Yeah That...*/
bool Tower::score() {
	cout << "Towers cannot score!"<< endl;
	return false;
}

/*
Just making sure...*/
bool Tower::move_to(Cell* destination) {
	cout << "towers cant move derp!"<< endl;
	return false;
}

/*
Input:
	target the unit should attack if possible.
Function:
	Same as Units */
bool Tower::attack_unit(Unit *target) {
	if (!canAct || health < 0) {
		cout << "Tower at " << position->get_X() << " " << position->get_Y() << " can not attack because of fatigue" << endl;
		return false;
	}

	if (is_in_range(target->get_position())) {
		target->damage_unit(attackStrength);
		deactivate();
		cout << "Tower at: " << position->get_X() << " " << position->get_Y() << " attacked Unit at:  " << target->get_position()->get_X() << " " << target->get_position()->get_Y() << endl;
		return true;
	}

	return false;
}

/*
Input:
	Owner: player 1 or 2
Function:
	Constructor for Missile Towers.
*/
MissileTower::MissileTower(int o):Tower( o) {
	MissileTower::set_signature('I');
	health = maxHealth = 10;
	range = 2;
	attackStrength = 2;
	cost = 3;

}

/*
Input:
	target the unit should attack if possible.
Function:
	Same as Units. Just there for cout and debug  */
bool MissileTower::attack_unit(Unit *target) {
	if (!canAct || health < 0) {
		cout << "Missile Tower at " << position->get_X() << " " << position->get_Y() << " can not attack because of fatigue" << endl;
		return false;
	}

	if (is_in_range(target->get_position())) {
		target->damage_unit(attackStrength);
		deactivate();
		cout << "Missile Tower at: " << position->get_X() << " " << position->get_Y() << " attacked Unit at:  " << target->get_position()->get_X() << " " << target->get_position()->get_Y() << endl;
		return true;
	}

	return false;
}

/*
Input:
Owner: player 1 or 2
Function:
Constructor for Rocket Towers.
*/
RocketTower::RocketTower(int o) : Tower( o) {
	RocketTower::set_signature('T');
	health = maxHealth = 10;
	range = 2;
	attackStrength = 1;
	cost = 3;
}

/*
Input:
	target the unit should attack if possible.
Function:
	Similar to Units attack_unit but also damages all units on the same field as the target.  */
bool RocketTower::attack_unit(Unit *target) {
	if (!canAct || health < 0) {
		cout << "Rocket Tower at " << position->get_X() << " " << position->get_Y() << " can not attack because of fatigue" << endl;
		return false;
	}

	if (is_in_range(target->get_position())) {
		auto localcop = target->get_position()->get_occupants();
		for (vector<Unit*>::iterator  it = localcop.begin(); it != localcop.end(); it++) {
			(*it)->damage_unit(attackStrength);
		}
		
		deactivate();
		cout << "Rocket Tower at: " << position->get_X() << " " << position->get_Y() << " attacked Unit at:  " << target->get_position()->get_X() << " " << target->get_position()->get_Y() << endl;
		return true;
	}

	return false;
}

/*
Input:
Owner: player 1 or 2
Function:
Constructor for Frost Towers.
*/
FrostTower::FrostTower(int o) : Tower( o) {
	FrostTower::set_signature('F');
	freezes = true;
	health = maxHealth = 10;
	range = 1;
	attackStrength = 1;
	cost = 3;
}

/*
Input:
	target the unit should attack if possible.
Function:
	Similar units attack function nut also deactivates attacked unit  */
bool FrostTower::attack_unit(Unit *target) {
	if (!canAct || health < 0) {
		cout << "Frost Tower at " << position->get_X() << " " << position->get_Y() << " can not attack because of fatigue" << endl;
		return false;
	}

	if (is_in_range(target->get_position())) {
		target->damage_unit(attackStrength);
		target->deactivate();
		deactivate();
		cout << "Frost Tower at: " << position->get_X() << " " << position->get_Y() << " attacked Unit at:  " << target->get_position()->get_X() << " " << target->get_position()->get_Y() << endl;
		return true;
	}

	return false;
}

/*
Input:
	Owner: player 1 or 2
Function:
	Constructor for Blockade.
*/
Blockade::Blockade(int o) : Tower(o) {
	Blockade::set_signature('X');
	health = maxHealth = 30;
	range = 0;
	attackStrength = 0;
	cost = 1;
}

/*
Input 
	Target that will not be attacked.
Function:
	Nothing really.
	*/
bool Blockade::attack_unit(Unit *target) {
	cout << "Blockades can't attack" << endl;
	return false;

}

/*
Input:
	Owner: Player 1 or 2
Function:
	Constructor of Soldier superclass*/
Soldier::Soldier(int o): Unit(o) {
	position = nullptr;

}

/*
Input:
	cell to which this unit will be deployed.
Function:
	Sets soldier position for deployment.
Return:
	True since soldiers can be deployed.
*/
bool Soldier::deploy(Cell* c) {
	position = c;
	return true;
}

/*
Input:
	pointer to Cell to which the unit tries to move
Function:
	Moves Soldier to destination if the destination is not blocked or the soldier is dead or deactivated.
	Deactivates soldier after action.
Return:
	True if move succeeded, false otherwise.*/
bool Soldier::move_to(Cell* destination) {
	if(abs(position->get_X() - destination->get_X()) <= speed && abs(position->get_Y() - destination->get_Y()) <= speed && !destination->is_blocked() && canAct && health > 0 && position->move_unit_to(*this, destination)) {
		cout << "soldier Moved from: "<< position->get_X() << " " << position->get_Y() << " to: " << destination->get_X() << " " << destination->get_Y() << endl;
		position = destination;
		deactivate();
		
		return true;
	}
	else 
		return false; 
}

/*
Function:
	Get Function for soldier speed.
Return:
	The soldiers speed. 
*/
int Soldier::get_speed() {
	return speed;
}

/*
Function:
	Checks if the soldier can score.
	If so, he is killed and set to score = true
Return True if soldier could score, false otherwise.*/

bool Soldier::score() {
	if (position->get_Y() != 0) {
		cout << "Unit has to reach the end of the lane!" << endl;
		return false;
	}
	else
	{
		if (!canAct || health <= 0) {
			cout << "This Unit can not act!" << endl;
			return false;
		}
		else
		{
			cout << "score!" << endl;
			health = 0;
			deactivate();
			scored = true;
			return true;
		}
	}
}

/*
Same as Units attack_unit function.  
*/
bool Soldier::attack_unit(Unit *target) {
	if (!canAct || health < 0) {
		cout << "Unit at " << position->get_X() << " " << position->get_Y() << " can not attack because of fatigue" << endl;
		return false;
	}

	if (is_in_range(target->get_position())) {
		target->damage_unit(attackStrength);
		deactivate();
		cout << "Unit at: " << position->get_X() << " " << position->get_Y() << " attacked Unit at:  " << target->get_position()->get_X() << " " << target->get_position()->get_Y() << endl;
		return true;
	}

	return false;
}

/*
Input:
	Owner: player 1 or 2
Function:
	Constructor for ShieldSoldiers.
*/
ShieldSoldier::ShieldSoldier(int o) :Soldier(o) {
	ShieldSoldier::set_signature('D');
	health = maxHealth = 5;
	speed = 1;
	range = 0;
	attackStrength = 1; 
	cost = 2;
}
/*
Same as Units attack_unit function.
Just there for debug and cout
*/
bool ShieldSoldier::attack_unit(Unit *target) {
	if (!canAct || health < 0) {
		cout << "Shield Soldier at " << position->get_X() << " " << position->get_Y() << " can not attack because of fatigue" << endl;
		return false;
	}

	if (is_in_range(target->get_position())) {
		target->damage_unit(attackStrength);
		deactivate();
		cout << "Shield Soldier at: " << position->get_X() << " " << position->get_Y() << " attacked Unit at:  " << target->get_position()->get_X() << " " << target->get_position()->get_Y() << endl;
		return true;
	}

	return false;
}

/*
Input:
Owner: player 1 or 2
Function:
Constructor for RifleSoldiets.
*/
RifleSoldier::RifleSoldier(int o) : Soldier(o) {
	RifleSoldier::set_signature('L');
	health = maxHealth = 3;
	speed = 1;
	range = 2;
	attackStrength = 1;
	cost = 2;
}

/*
Same as Units attack_unit function.
Just there for debug and cout
*/
bool RifleSoldier::attack_unit(Unit *target) {
	if (!canAct || health < 0) {
		cout << "Rifle Soldier at " << position->get_X() << " " << position->get_Y() << " can not attack because of fatigue" << endl;
		return false;
	}

	if (is_in_range(target->get_position())) {
		target->damage_unit(attackStrength);
		deactivate();
		cout << "Rifle Soldier at: " << position->get_X() << " " << position->get_Y() << " attacked Unit at:  " << target->get_position()->get_X() << " " << target->get_position()->get_Y() << endl;
		return true;
	}

	return false;
}

/*
Input:
Owner: player 1 or 2
Function:
Constructor for Bombsoldiers.
*/
BombSoldier::BombSoldier(int o) : Soldier(o) {
	BombSoldier::set_signature('Q');
	health = maxHealth = 3;
	speed = 1;
	range = 1;
	attackStrength = 3; 
	cost = 3;
}

/*
Same as Units attack_unit function.
Just there for debug and cout
*/
bool BombSoldier::attack_unit(Unit *target) {
	if (!canAct || health < 0) {
		cout << "Bomb Soldier at " << position->get_X() << " " << position->get_Y() << " can not attack because of fatigue" << endl;
		return false;
	}

	if (is_in_range(target->get_position())) {
		target->damage_unit(attackStrength);
		deactivate();
		cout << "Bomb Soldier at: " << position->get_X() << " " << position->get_Y() << " attacked Unit at:  " << target->get_position()->get_X() << " " << target->get_position()->get_Y() << endl;
		return true;
	}

	return false;
}

/*
Input:
	Owner: player 1 or 2
Function:
	Constructor for HorseSoldiers.
*/
HorseSoldier::HorseSoldier(int o) : Soldier(o) {
	HorseSoldier::set_signature('M');
	health = maxHealth = 3;
	speed = 2;
	range = 1;
	attackStrength = 1;
	cost = 3;
}

/*
Same as Units attack_unit function.
Just there for debug and cout
*/
bool HorseSoldier::attack_unit(Unit *target) {
	if (!canAct || health < 0) {
		cout << "Horse Soldier at " << position->get_X() << " " << position->get_Y() << " can not attack because of fatigue" << endl;
		return false;
	}

	if (is_in_range(target->get_position())) {
		target->damage_unit(attackStrength);
		deactivate();
		cout << "Horse Soldier at: " << position->get_X() << " " << position->get_Y() << " attacked Unit at:  " << target->get_position()->get_X() << " " << target->get_position()->get_Y() << endl;
		return true;
	}

	return false;
}