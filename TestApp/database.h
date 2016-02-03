
#include "stdafx.h"
#include "unit.h"

class cDatabase
{
public:
	adv::cDatabase<cUnit> Unit;
	adv::cDatabase<cEnemy> Enemy;
	adv::cDatabase<cMissile> Missile;
};

extern cDatabase Database;