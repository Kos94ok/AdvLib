
#include "stdafx.h"
#include "event.h"
#include "timer.h"

void adv::cTimerMain::__threadMain(int id, cArgs args)
{
	cTimer* tmr;
	float timevar = 0.00f;
	int elapsedTime = 0;
	int globalTimeNew = 0;
	int globalTimeOld = timeGetTime();

	advCore.threadState[id] = STATE_UP;
	do
	{
		// Updating the time values
		globalTimeNew = timeGetTime();
		elapsedTime = globalTimeNew - globalTimeOld;
		timevar = (float)elapsedTime / 1000.00f;
		globalTimeOld = globalTimeNew;

		// Checking all the timers
		for (int i = 0; i < advTimer.__getTimerCount(); i++) {
			// Getting the timer handle
			tmr = advTimer.__getTimerHandle(i);
			// Checking the remaining time
			if (tmr->timeCur > 0.00f) {
				// If the remaining time is more than zero, reduce the remaining time
				tmr->timeCur -= timevar;
				tmr->tickTime += elapsedTime;
				// If the new remaining time is zero, check the repeat flag
				if (tmr->timeCur <= 0.00f) {
					if (tmr->repeat) {
						// If the timer is repeatable, create a 'tick' event
						cEventArgs eventArgs(tmr->id, tmr->name);
						eventArgs.timer_tickTime = tmr->tickTime;
						eventArgs.timer_tickDelay = tmr->timeMax;
						advEvent.add(EVENT_TIMER_TICK, eventArgs, FAMILY_GENERIC);
						// And then restart
						tmr->timeCur = tmr->timeMax;
						tmr->tickTime = 0;
					}
					else {
						// Create an 'end' event
						cEventArgs eventArgs(tmr->id, tmr->name);
						eventArgs.timer_tickTime = tmr->tickTime;
						eventArgs.timer_tickDelay = tmr->timeMax;
						advEvent.add(EVENT_TIMER_END, eventArgs, FAMILY_GENERIC);
						// Then remove, if the timer is not repeatable
						advTimer.__removeTimer(i);
						i -= 1;
					}
				}
			}
		}
		Sleep(1);
	} while (advCore.isThreadGood(id));
	advCore.threadState[id] = STATE_DOWN;
}