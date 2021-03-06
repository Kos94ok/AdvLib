
#include "stdafx.h"

class cCamera
{
	sf::Mutex access;
public:
	vec2f Anchor;
	vec2f Position;
	vec2f TargetPosition;
	vec2f MainSize = vec2f(800, 600);
	vec2f MainOffset = vec2f(400, 0);

	void Lock() { access.lock(); }
	void Unlock() { access.unlock(); }
	void AnchorTo(vec2f AnchorPos) { Anchor = AnchorPos; }
	void MoveTo(vec2f NewPosition) { Position = NewPosition; }
	void AccelerateTo(vec2f NewPosition) { TargetPosition = NewPosition; }

	static void TimerAcceleration(adv::cEventArgs args);
	static void EventMouseMove(adv::cEventArgs args);
};

extern cCamera Camera;