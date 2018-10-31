#pragma once
#ifndef UNIT_H
#define UNIT_H
using namespace std;
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <cmath>
class Cell;

class Unit
{
public:
	Unit(int o);
	void set_signature(char sig);
	char get_signature();
	int get_owner();
	Cell* get_position();
	void set_owner(int i);
	bool is_active();
	int get_range();
	virtual bool attack_unit(Unit *target);
	void damage_unit(int damage);
	int get_health();
	void reset();
	bool is_in_range(Cell* c);
	virtual bool deploy(Cell* c);
	virtual bool score();
	virtual bool move_to(Cell* destination);
	virtual bool place_tower(Cell* c, int* money);
	void activate();
	bool has_scored();
	int* get_cost();
	void deactivate();
protected:
	
	
	int owner;
	char signature;
	Cell* position;
	int health;
	int maxHealth;
	bool canAct = true;
	int attackStrength;
	int range;
	bool freezes = false;
	bool scored = false;
	int cost;
private:

	
};

class Empty : public Unit
{
public:
	Empty();

};


class Tower : public Unit
{
public:
	Tower(int o);
	bool score();
	bool move_to(Cell* destination);
	bool place_tower(Cell* c, int* money);
	virtual bool attack_unit(Unit *target);

protected:
private:

};

class MissileTower : public Tower
{
public:
	MissileTower( int o);
	bool attack_unit(Unit *target);
protected:
private:

};


class RocketTower : public Tower
{
public:
	RocketTower( int o);
	bool attack_unit(Unit *target);
protected:
private:

};

class FrostTower : public Tower
{
public:
	FrostTower( int o);
	bool attack_unit(Unit *target);
protected:
private:

};

class Blockade : public Tower
{
public:
	Blockade( int o);
	bool attack_unit(Unit *target);
protected:
private:

};


class Soldier : public Unit
{
public:
	Soldier(int o);
	int get_speed();
	bool move_to(Cell* destination);
	bool deploy(Cell* c);
	bool score();
	virtual bool attack_unit(Unit *target);

protected:
	int speed;


private:

};

class ShieldSoldier : public Soldier
{
public:
	ShieldSoldier(int o);
	bool attack_unit(Unit *target);
protected:
private:

};

class RifleSoldier : public Soldier
{
public:
	RifleSoldier(int o);
	bool attack_unit(Unit *target);
protected:
private:

};

class BombSoldier : public Soldier
{
public:
	BombSoldier(int o);
	bool attack_unit(Unit *target);
protected:
private:

};

class HorseSoldier : public Soldier
{
public:
	HorseSoldier(int o);
	bool attack_unit(Unit *target);
protected:
private:

};


#endif