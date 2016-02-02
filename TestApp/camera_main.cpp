
#include "stdafx.h"
#include "camera.h"

cCamera Camera;

void cCamera::TimerAcceleration(adv::cEventArgs args)
{
	float timemod = args.timer_tickDelay;

	Camera.Position = advMath.polar(Camera.Position, advMath.getDistance(Camera.Position, Camera.Anchor) / 50, advMath.getAngle(Camera.Position, Camera.Anchor));
}

void cCamera::EventMouseMove(adv::cEventArgs args)
{
	//Camera.TargetPosition = args.posF;
	//Camera.Position = args.posF;
}