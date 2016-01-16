
#include "stdafx.h"
#include "event.h"
#include "timer.h"

void adv::cTimerMain::__threadMain(int id, cArgs args)
{
	cTimer* tmr;
	cTimerDynamic* dtmr;
	float timevar = 0.00f;
	int elapsedTime = 0;
	int globalTimeNew = 0;
	int globalTimeOld = timeGetTime();
	do
	{
		advTimer.__access.lock();
		// Updating the time values
		globalTimeNew = timeGetTime();
		elapsedTime = globalTimeNew - globalTimeOld;
		timevar = (float)elapsedTime / 1000.00f;
		globalTimeOld = globalTimeNew;

		// Checking static timers
		for (int i = 0; i < advTimer._getTimerCount(); i++)
		{
			// Getting the timer handle
			tmr = advTimer._getTimerHandle(i);
			// Checking the remaining time
			if (tmr->timeCur > 0.00f) {
				// If the remaining time is more than zero, reduce the remaining time
				tmr->timeCur -= timevar;
				tmr->tickTime += elapsedTime;
				// If the new remaining time is zero, check the repeat flag
				if (tmr->timeCur <= 0.00f) {
					// Create a 'tick' event
					cEventArgs eventArgs(tmr->id, tmr->name);
					eventArgs.timer_tickTime = tmr->tickTime;
					eventArgs.timer_tickDelay = tmr->timeMax;
					advEvent.add(EVENT_TIMER_TICK, eventArgs);
					// Restart the timer
					tmr->timeCur = tmr->timeMax;
					tmr->tickTime = 0;
				}
			}
		}
		// Checking dynamic timers
		for (int i = 0; i < advTimer._getTimerDynamicCount(); i++)
		{
			// Getting the timer handle
			dtmr = advTimer._getTimerDynamicHandle(i);
			// Checking the remaining time
			if (dtmr->timeCur > 0.00f) {
				// If the remaining time is more than zero, reduce the remaining time
				dtmr->timeCur -= timevar;
				dtmr->tickTime += elapsedTime;
				// If the new remaining time is zero, check the repeat flag
				if (dtmr->timeCur <= 0.00f) {
					// Call event handler directly
					cEventArgs eventArgs = dtmr->tickArgs;
					eventArgs.timer_tickTime = dtmr->tickTime;
					eventArgs.timer_tickDelay = dtmr->timeMax;
					advEvent.__getHandlerQueue()->add(dtmr->tickHandler, eventArgs);
					// Check the TTL
					if (dtmr->ttl > 1 || dtmr->ttl == -1)
					{
						// If the timer is repeatable, restart
						dtmr->ttl -= 1;
						dtmr->timeCur = dtmr->timeMax;
						dtmr->tickTime = 0;
					}
					else
					{
						// If the timer is not repeatable, remove
						advTimer._removeTimerDynamic(i);
						i -= 1;
					}
				}
			}
		}
		advTimer.__access.unlock();
		Sleep(1);
	} while (advCore.isThreadGood(id));
	advCore.stopThread(id);
}