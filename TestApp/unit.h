
#pragma once

#include "stdafx.h"
#include "plane.h"

class cScene;

class cHover
{
public:
	int HoverTimer = 0;
	float HoverTimeMod = 1.00f;
	float HoverMagnitude = 0.00f;
};

class cUnit : public adv::cAnimatedDrawable
{
public:
	cScene* HomeScene;

	float HP;
	string Type;
	int Plane = cPlane::Gameplay;
};

class cMovingUnit : public cUnit, public cHover
{
public:
	int Facing = cFacing::Left;
	float VertAccel = 0.f;

	bool CheckRising();
	bool CheckFalling();

	void updateBrush();
	void updateBrushPos();
	void updateBrushPrepaint();
	void MoveHover(int time);
	void AddHover(float magnitude, float timeMod);
	void SetFacing(int NewFacing) { Facing = NewFacing; }
};

class cHero : public cMovingUnit
{
public:
	enum Weapon
	{
		Soulshard,
	};

	int ActiveWeapon = cHero::Weapon::Soulshard;
	int JumpCount = 0;
	float WeaponCooldown = 0.00f;

	void Jump(adv::cEventArgs args);
	void Respawn(adv::cEventArgs args);
	void Shoot(adv::cEventArgs args);

	void TimerShooting(adv::cEventArgs args);

	cHero(){}
};

class cEnemy : public cMovingUnit
{
public:
	int AttackType;

	enum AttackType
	{
		SnakeShooting,
	};
};

class cMissile : public cUnit
{
public:
	vec2f MovingVector;
	int Owner;
	float Facing = 0.00f;
	float RotationSpeed = 0.00f;
	bool LifeTimerEnabled = false;
	float LifeTimer = -1.00f;

	void AddRotation(float Speed) { RotationSpeed = Speed; }
	void AddLifeTimer(float LifeTimer) { this->LifeTimer = LifeTimer; LifeTimerEnabled = true; }
};