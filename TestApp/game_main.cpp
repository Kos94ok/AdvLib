
#include "stdafx.h"
#include "game.h"

cGame Game;

bool cUnit::CheckRising()
{
	for (cUnit unit : Game.TestScene.UnitList)
	{
		if (unit.pos() != this->pos() && unit.size() != this->size())
		{
			if (pos().x + size().x >= unit.pos().x && pos().x <= unit.pos().x + unit.size().x
				&& pos().y <= unit.pos().y + unit.size().y - VertAccel / 2 && pos().y >= unit.pos().y + unit.size().y + VertAccel / 2)
			{
				VertAccel = 0.0f;
				return false;
			}
		}
	}
	return true;
}

bool cUnit::CheckFalling()
{
	for (cUnit unit : Game.TestScene.UnitList)
	{
		if (unit.pos() != this->pos() && unit.size() != this->size())
		{
			if (pos().x + size().x >= unit.pos().x && pos().x <= unit.pos().x + unit.size().x
				&& pos().y + size().y >= unit.pos().y - VertAccel / 2 && pos().y + size().y <= unit.pos().y + VertAccel / 2)
			{
				moveto(vec2f(pos().x, unit.pos().y - size().y));
				return false;
			}
		}
	}
	return true;
}

void cHero::Jump(adv::cEventArgs args)
{
	if (!CheckFalling())
	{
		JumpCount = 1;
		VertAccel = -5.00f;
	}
	else if (JumpCount < 2)
	{
		JumpCount += 1;
		if (VertAccel >= 0.00f) VertAccel = -3.00f;
		else VertAccel -= 3.00f;
	}
}

void cHero::Respawn(adv::cEventArgs args)
{
	moveto(vec2f(0, 0));
}

void cGame::TimerHeroMovement(adv::cEventArgs args)
{
	float timemod = args.timer_tickDelay;

	float speedX = 250.00f * timemod;
	float accY = 10.f * timemod;
	cUnit* hero = &Game.Hero;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		hero->move(vec2f(-speedX, 0.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		hero->move(vec2f(speedX, 0.f));
	}

	if (hero->VertAccel >= 0.00f && hero->CheckFalling())
	{
		hero->move(vec2f(0.f, hero->VertAccel));
		hero->VertAccel += accY;
	}
	else if (hero->VertAccel < 0.00f && hero->CheckRising())
	{
		hero->move(vec2f(0.f, hero->VertAccel));
		hero->VertAccel += accY;
	}
	else
	{
		hero->VertAccel = 0.00f;
	}
}