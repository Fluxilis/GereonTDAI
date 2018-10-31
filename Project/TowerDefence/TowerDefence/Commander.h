#pragma once
#ifndef COMMANDER_H
#define COMMANDER_H
using namespace std;
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Cell.h"
#include "Unit.h"
#include "UnitAI.h"
#include "UnitAI.h"


struct Depoyment
{
	int pos;
	int wave;
	UnitAI* unit;
};
class Commander
{	
public:
	Commander(int id, int w, int h);
	int width;
	int hight;
	int get_id();
	virtual void build_turrets(Cell *** &lane);
	int update_towers();
	virtual void recrute_soldiers();
	virtual vector<Depoyment*>* deploy();
	virtual vector<UnitAI*>* get_towers();
	virtual vector<UnitAI*>* get_soldiers();
	void recieve_funds(int funds);
	bool salary_paid(UnitAI* u);

protected:
	int id;
	vector<UnitAI*> towers;
	vector<UnitAI*> army;
	int money;
private:
	

};

class CommanderA : public Commander {

public :
	int counter;
	CommanderA(int id, int w, int h);
	void build_turrets(Cell *** &lane);
	void recrute_soldiers();
	vector<UnitAI*>* get_towers();
	vector<UnitAI*>* get_soldiers();
	vector<Depoyment*>* deploy();

protected:

private:
	int switchi;

};

class CommanderB : public Commander {

public:
	int counter;
	CommanderB(int id, int w, int h);
	void build_turrets(Cell *** &lane);
	void recrute_soldiers();
	vector<UnitAI*>* get_towers();
	vector<UnitAI*>* get_soldiers();
	vector<Depoyment*>* deploy();
protected:

private:


};

#endif
