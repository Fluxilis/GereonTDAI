#pragma once
#ifndef UNITAI_H
#define UNITAI_H
using namespace std;
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include"Unit.h"
class Cell;

class UnitAI
{
public:
	const int WIDTH = 7;
	const int HIGHT = 20;
	UnitAI();
	UnitAI(Unit* u);
	Unit* get_unit();
	virtual void tower_action(Cell*** lane);
	virtual void soldier_action(Cell*** lane);

private:

protected:
	 Unit* unit;


};

class EmptyAI : public UnitAI 
{
public:
	EmptyAI(Unit* u);
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
class TowerAIA : public UnitAI
{
public:
	TowerAIA();
	TowerAIA(Unit* u);
	void tower_action(Cell*** lane);
protected:
private:


};



class MissileAIA : public TowerAIA
{
public:
	MissileAIA(Unit* u);
private:
protected:

};

class RocketAIA : public TowerAIA
{
public:
	RocketAIA(Unit* u);
private:
protected:

};

class FrostAIA : public TowerAIA
{
public:
	FrostAIA(Unit* u);
private:
protected:

};

class BlockadeAIA : public TowerAIA
{
public:
	BlockadeAIA(Unit* u);
private:
protected:

};




class SoldierAIA : public UnitAI
{
public:
	SoldierAIA();
	SoldierAIA(Unit* u);
	void soldier_action(Cell*** lane);
protected:
private:


};

class ShieldAIA : public SoldierAIA
{
public:
	ShieldAIA(Unit* u);
protected:
private:


};

class RifleAIA : public SoldierAIA
{
public:
	RifleAIA(Unit* u);
protected:
private:


};

class BombAIA : public SoldierAIA
{
public:
	BombAIA(Unit* u);
protected:
private:


};

class HorseAIA : public SoldierAIA
{
public:
	HorseAIA(Unit* u);
	void soldier_action(Cell*** lane);
protected:
private:


};
///////////////////////////////////////////////////////////
















#endif
