
#include "stdafx.h"

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
	float HP;
	string Type;
	float VertAccel = 0.f;
};

class cMovingUnit : public cUnit, public cHover
{
public:
	bool CheckRising();
	bool CheckFalling();

	void updateBrush();
	void updateBrushPos();
	void MoveHover(int time);
	void AddHover(float magnitude, float timeMod);
};

class cHero : public cMovingUnit
{
public:
	int JumpCount = 0;

	void Jump(adv::cEventArgs args);
	void Respawn(adv::cEventArgs args);

	cHero(){}
};

class cEnemy : public cMovingUnit
{

};

class cScene
{
public:
	bool Visible = false;

	adv::vectox<cUnit> UnitList;

	void paint(sf::RenderTexture* texHandle, sf::Transform matrix = sf::Transform())
	{
		UnitList.lock();
		for (int i = 0; i < (int)UnitList.size(); i++)
		{
			UnitList[i].paint(texHandle, matrix);
		}
		UnitList.unlock();
	}
};

class cGame
{
public:
	cHero Hero;
	cScene TestScene;

	static void TimerAnimation(adv::cEventArgs args);
	static void TimerHeroMovement(adv::cEventArgs args);
};

extern cGame Game;