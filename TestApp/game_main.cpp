
#include "stdafx.h"
#include "game.h"
#include "camera.h"

cGame Game;

void cMovingUnit::MoveHover(int time)
{
	HoverTimer += time;
	updateBrushPos();
}

void cMovingUnit::AddHover(float magnitude, float timeMod)
{
	HoverMagnitude = magnitude;
	HoverTimeMod = timeMod;
}

void cMovingUnit::updateBrush()
{
	adv::cAnimatedDrawable::updateBrush();
	brushRect.move(vec2f(0.00f, HoverMagnitude * sin((float)HoverTimer / 100 * HoverTimeMod)));
}

void cMovingUnit::updateBrushPos()
{
	adv::cAnimatedDrawable::updateBrushPos();
	brushRect.move(vec2f(0.00f, HoverMagnitude * sin((float)HoverTimer / 100 * HoverTimeMod)));
}

bool cMovingUnit::CheckRising()
{
	sf::FloatRect myRect(pos() - center(), size());
	for (cUnit unit : Game.TestScene.UnitList)
	{
		if (unit.pos() != this->pos() && unit.size() != this->size())
		{
			sf::FloatRect theirRect(unit.pos() - unit.center() + vec2f(0.f, -VertAccel / 2), unit.size() + vec2f(0.f, VertAccel / 2));
			if (myRect.left + myRect.width >= theirRect.left && myRect.left <= theirRect.left + theirRect.width
				&& myRect.top >= theirRect.top && myRect.top <= theirRect.top + theirRect.height)
			{
				VertAccel = 0.0f;
				return false;
			}
		}
	}
	return true;
}

bool cMovingUnit::CheckFalling()
{
	sf::FloatRect myRect(pos() - center(), size());
	for (cUnit unit : Game.TestScene.UnitList)
	{
		if (unit.pos() != this->pos() && unit.size() != this->size())
		{
			sf::FloatRect theirRect(unit.pos() - unit.center() + vec2f(0.f, -VertAccel / 2), unit.size() + vec2f(0.f, VertAccel / 2));
			if (myRect.left + myRect.width >= theirRect.left && myRect.left <= theirRect.left + theirRect.width
				&& myRect.top + myRect.height >= theirRect.top && myRect.top + myRect.height <= theirRect.top + theirRect.height)
			{
				moveto(vec2f(pos().x, unit.pos().y - unit.center().y - size().y + center().y));
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

void cGame::TimerAnimation(adv::cEventArgs args)
{
	float timemod = args.timer_tickDelay;

	cHero* hero = &Game.Hero;
	hero->moveAnim(timemod * 1000);
}

void cGame::TimerHeroMovement(adv::cEventArgs args)
{
	float timemod = args.timer_tickDelay;

	float speedX = 250.00f * timemod;
	float accY = 10.f * timemod;
	Camera.Lock();
	cHero* hero = &Game.Hero;
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
	//Camera.MoveTo(vec2f(hero->pos().x, 0.00f));
	Camera.AnchorTo(vec2f(hero->pos().x, 0.00f));
	Camera.Unlock();

	hero->MoveHover(timemod * 1000);
}