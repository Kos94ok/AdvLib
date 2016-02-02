
#include "stdafx.h"

class cUnit : public adv::cAnimatedDrawable
{
public:
	float hp;
	string type;
	float vertAccel = 0.f;
};

class cHero : public cUnit
{
public:
	// Events
	void jump(adv::cEventArgs args)
	{
		if (args.id != sf::Keyboard::W) { return; }

		//cUnit* hero = &testScene.unitList[0];
		if (pos().y >= 590 - size().y + center().y)
		{
			vertAccel = -10.00f;
		}
	}
};

class cGame
{
public:
	cHero Hero;
	adv::vectox<cUnit> Unit;
};

class cScene
{
public:
	bool visible = false;

	adv::vectox<cUnit> unitList;

	void paint(sf::RenderTexture* texHandle, sf::Transform matrix = sf::Transform())
	{
		unitList.lock();
		for (int i = 0; i < (int)unitList.size(); i++)
		{
			unitList[i].paint(texHandle, matrix);
		}
		unitList.unlock();
	}
};

cGame Game;