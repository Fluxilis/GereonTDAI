#include "Cell.h"

const int WIDTH = 7;


/*
Input:
	Reference to unit, to look for.
Function:
	Finds unit in occupants.
	Only works when sure that Unit is in occupants!!!!!
Return:
	Return iterator pointing to searched for object.
	
*/
auto Cell::find_occupant(Unit &oc) {
	auto first = occupant.begin();
	auto last = occupant.end();
	while (first != last) {
		if (*first == &oc) {
			return first;
		}
		++first;

	}
}

/*
Function:
	Get Function for occupants of cell.
Return:
	vector of pointers to the occupant units. 
*/
vector<Unit *> Cell::get_occupants() {
	return occupant;
}


/*
Function:
	Prints the cell for output.
	Only the last element is printed.
	output contains another string necessary to complete output pattern*/
void Cell:: printCell() {
	cout << occupant.back()->get_signature() << "  |  ";
}

/*
Input: 
	Reference to unit to be added to the cell
Function:
	adds Unit to the occupants if the cell is not blocked.
Return: True if unit was successfully added, false otherwise.*/

bool Cell::add_occupant(Unit &oc) {
	if (oc.get_owner() == 0) {
		cout << "invalid order" << endl;
		return false;
	}
	if (!blocked) {
		occupant.push_back(&oc);
		return true;
	}
	else
	{
		cout << " invalid move canceled" << endl;
		return false;
	}
}

/*
Input:
	Occupant to be removed
Function:
	Removes given occupant from occupant list.
Return:
	True if successfully removed, false otherwise.
	*/
bool Cell::remove_occupant(Unit &oc) {
	for (vector<Unit*>::iterator it = occupant.begin(); it != occupant.end(); it ++) {
		if ((*it) == &oc) {
			occupant.erase(find_occupant(oc));
			return true;
		}
		
	}
	return false;
		
}

/*
Input:
	Tower to be removed
Function:
	Removes tower and unblocks the cell.
Return:
	True if successful.*/
bool Cell::remove_tower(Unit &oc) {
	if (remove_occupant(oc)) {
		unblock();
		return true;
	}
	return false;
}

/*
Function:
	Get Function for x position(width) of the cell in lane.lane position given as lane[y][x]
Return:
	x position of cell in lane*/
int Cell::get_X() {
	return x;
}

/*
Function:
Get Function for y position(hight) of the cell in lane.lane position given as lane[y][x]
Return:
y position of cell in lane*/
int Cell::get_Y() {
	return y;
}

/*
Input:
	oc: Reference to occupant unit(starts with empty cell)
	xpos: Cells x position (width)
	ypos: Cells y position (hight)
	l : the lane of which the cell is a part.
Function:
	Constructor of Cell
	*/
Cell::Cell(Unit  &oc, int xpos, int ypos, Cell*** l):fallback(oc)
{
	occupant.push_back(&oc);
	x = xpos;
	y = ypos;
	lane = l;
}

/*
Function:
	Get function for whether the cell is blocked.
Return:
	boolean of the cell is blocked*/
bool Cell::is_blocked() {
	return blocked;
}

/*
Function:
	sets the Cell to blocked.
*/
void Cell::block() {
	blocked = true;
}

/*
Function:
	Sets the cell to not blocked.*/
void Cell::unblock() {
	blocked = false;
}

/*
Function:
	Determines whether the line is full, be checking if there is only one open space left. 
	Line will be determined not full if there are 2 or more unblocked cells.
return:
	True if only 0 or 1 Cells line are not blocked
*/
bool Cell::line_full() {
	int filled = 0;
	for (int i = 0; i < WIDTH ; i++) {
		if (lane[get_Y()][i]->is_blocked())
			filled++;
	}
	if(filled > WIDTH-1){
		return true;
	}
	else
	{
		return false;
	}
}

/*
Input:
	Reference of tower to be build in cell
Function:
	Adds Tower to occupants and blocks cell if cell is not blocked or there is only 1 unblocked cell in the line left.
Return:
	True if Tower was successfully added.
	*/
bool Cell::build_tower(Unit &oc) {
	if (blocked || line_full()) 
		return false;
	
	add_occupant(oc);
	block();
	return true;
}

/*
Input:
	Reference to Unit to be added.
Function:
	Adds Unit to occupants and sets unit to deploy to this cell.
Return:
	if the unit could be deployed
		
*/
bool Cell::deploy_unit(Unit &oc) {
	bool dep = oc.deploy(this);
	if (dep){
		add_occupant(oc);
	return true;
	}
	else {
		return false;
	}
 
}

/*
Input:
	owner id for player 1 or 2
Function:
	Searches for all Units in the cells occupant list, that belong to the other player
Return:
	Vector of unit pointers to all units belonging to the opposing player.*/
vector<Unit*> Cell::get_enemies(int owner) {
	vector<Unit*> enemies;
	for (vector<Unit*>::iterator it = occupant.begin(); it != occupant.end(); it++) {
		if ((*it)->get_owner() != 0 && (*it)->get_owner() != owner) {
			enemies.push_back((*it));
		}
	}

	return enemies;
}

/*
Input:
	oc: Unit to be moved.
	to: Cell the unit is moved to.
Function:
	Tries to move the Unit to the target cell.
Return:
	True on success.
*/
bool Cell::move_unit_to(Unit &oc, Cell* to) {
	if (to->add_occupant(oc)) {
		remove_occupant(oc);
		return true;
	}
	return false;
}