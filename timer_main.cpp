
#include "stdafx.h"
#include "event.h"
#include "timer.h"

adv::cTimerMain advTimer;

void adv::cTimerMain::init()
{
	if (initialized) { return; }
	initialized = true;

	advCore.addThread(__threadMain, 0);

	start(0.01f, TIMER_10MS, true);
	start(0.05f, TIMER_50MS, true);
	start(0.10f, TIMER_100MS, true);
	start(0.30f, TIMER_300MS, true);
	start(0.50f, TIMER_500MS, true);
	start(1.00f, TIMER_1000MS, true);
	start(2.00f, TIMER_2000MS, true);
	start(5.00f, TIMER_5000MS, true);
}

void adv::cTimerMain::start(float time, cTimerArgs args, bool repeat)
{
	access.lock();

	cTimer entry;
	entry.id = args.id;
	entry.name = args.name;
	entry.repeat = repeat;
	entry.timeCur = time;
	entry.timeMax = time;

	timerList.push_back(entry);
	advEvent.add(EVENT_TIMER_START, cEventArgs(args.id, args.name), FAMILY_GENERIC);

	access.unlock();
}

void adv::cTimerMain::__removeTimer(int number)
{
	access.lock();

	for (int i = number; i < __getTimerCount() - 1; i++) {
		timerList[i] = timerList[i + 1];
	}
	timerList.pop_back();

	access.unlock();
}