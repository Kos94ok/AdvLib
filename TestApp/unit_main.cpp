
#include "stdafx.h"
#include "unit.h"
#include "scene.h"

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

void cMovingUnit::updateBrushPrepaint()
{
	adv::cAnimatedDrawable::updateBrushPrepaint();
	if (Facing == cFacing::Right)
	{
		sf::IntRect TexRect = brushRect.getTextureRect();
		TexRect.left += TexRect.width;
		TexRect.width = -TexRect.width;
		brushRect.setTextureRect(TexRect);
	}
}

bool cMovingUnit::CheckRising()
{
	sf::FloatRect myRect(pos() - center(), size());
	for (cUnit unit : HomeScene->UnitList)
	{
		// Collision only allowed with the gameplay plane
		if (unit.Plane == cPlane::Gameplay && unit != this)
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
	for (cUnit unit : HomeScene->UnitList)
	{
		// Collision only allowed with the gameplay plane
		if (unit.Plane == cPlane::Gameplay && unit != this)
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