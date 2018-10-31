#pragma once
#ifndef CELL_H
#define CELL_H
using namespace std;
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Unit.h"

class Cell
{
	public:
		Cell(Unit &oc, int xpos, int ypos, Cell*** l);
		bool add_occupant(Unit &o);
		bool remove_occupant(Unit &oc);
		bool remove_tower(Unit &oc);
		void printCell();
		int get_X();
		int get_Y();
		auto find_occupant(Unit &oc);
		vector <Unit *>get_occupants();
		bool is_blocked();
		bool deploy_unit(Unit &oc);
		vector<Unit*> get_enemies(int owner);
		bool build_tower(Unit &oc);
		bool move_unit_to(Unit &oc, Cell* to);
		bool line_full();
	protected:

	private:
		Cell *** lane;
		vector <Unit *> occupant; 
		Unit & fallback;
		int x;
		int y;
		bool blocked = false;
		void block();
		void unblock();
};		



#endif