
#include "stdafx.h"
#include "event.h"
#include "timer.h"

adv::cTimerMain advTimer;

void adv::cTimerMain::init()
{
	if (__initialized) { return; }
	__initialized = true;

	advCore.addThread(__threadMain, 0);

	start(0.01f, TIMER_10MS);
	start(0.05f, TIMER_50MS);
	start(0.10f, TIMER_100MS);
	start(0.30f, TIMER_300MS);
	start(0.50f, TIMER_500MS);
	start(1.00f, TIMER_1000MS);
	start(2.00f, TIMER_2000MS);
	start(5.00f, TIMER_5000MS);
}

void adv::cTimerMain::start(float time, cTimerArgs args)
{
	__access.lock();

	for (int i = 0; i < (int)__timerList.size(); i++)
	{
		if ((args.id != MISSINGNO && args.id == __timerList[i].id) || (args.name != "" && args.name == __timerList[i].name))
		{
			advException.warning(WARNING::DUPTIMER, to_string(args.id) + " | " + args.name);
			return;
		}
	}

	cTimer entry;
	entry.id = args.id;
	entry.name = args.name;
	entry.timeCur = time;
	entry.timeMax = time;

	__timerList.push_back(entry);
	advEvent.add(EVENT_TIMER_START, cEventArgs(args.id, args.name));

	__access.unlock();
}

void adv::cTimerMain::startFor(float time, function<void(cEventArgs args)> entryFunc, int ttl, cEventArgs args)
{
	__access.lock();

	cTimerDynamic entry;
	entry.ttl = ttl;
	entry.timeCur = time;
	entry.timeMax = time;
	entry.tickArgs = args;
	entry.tickHandler = entryFunc;

	__timerDynamicList.push_back(entry);

	__access.unlock();
}

void adv::cTimerMain::_removeTimer(int number)
{
	__access.lock();

	for (int i = number; i < _getTimerCount() - 1; i++) {
		__timerList[i] = __timerList[i + 1];
	}
	__timerList.pop_back();

	__access.unlock();
}

void adv::cTimerMain::_removeTimerDynamic(int number)
{
	__access.lock();

	for (int i = number; i < _getTimerDynamicCount() - 1; i++) {
		__timerDynamicList[i] = __timerDynamicList[i + 1];
	}
	__timerDynamicList.pop_back();

	__access.unlock();
}