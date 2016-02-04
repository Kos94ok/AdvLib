
#include "stdafx.h"
#include "unit.h"

class cDatabase
{
public:
	adv::cDatabase<cUnit> Unit;
	adv::cDatabase<cEnemy> Enemy;
	adv::cDatabase<cMissile> Missile;

	const float Hero_Soulshard_Speed = 700.00f;
	const float Hero_Soulshard_LifeTime = 3.00f;
	const float Hero_Soulshard_Cooldown = 0.25f;
	const float Snake_Missile_Speed = 300.00f;
	const float Snake_Missile_LifeTime = 1.50f;
};

extern cDatabase Database;