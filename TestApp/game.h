
#include "stdafx.h"

class cUnit : public adv::cAnimatedDrawable
{
public:
	float HP;
	string Type;
	float VertAccel = 0.f;
};

class cMovingUnit : public cUnit
{
	bool CheckRising();
	bool CheckFalling();
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

	static void TimerHeroMovement(adv::cEventArgs args);
};

extern cGame Game;