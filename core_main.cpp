
#include "stdafx.h"
#include "core.h"
#include "event.h"
#include "timer.h"
#include "mouse.h"
#include "ui.h"

adv::cCore advCore;
adv::cValueTown advValue;
adv::cExceptionMain advException;

void adv::cCore::init()
{
	advEvent.init();			// Must be first
	advTimer.init();			// Must be second

	advMouse.__init();
	advUI.init();

	advCore.postInit();			// Must be last
}

void adv::cCore::postInit()
{
	advEvent.add(EVENT_INIT, -1, FAMILY_POST);
}

void adv::cCore::shut()
{
	advEvent.add(EVENT_PRESHUT, -1, FAMILY_POST);
	int threadCount = __threadPool.size();
	// Checking all the threads in reverse order
	for (int i = threadCount - 1; i >= 0; i--) {
		if (__threadState[i] == STATE_UP) {
			__threadState[i] = STATE_SHUTTING;
			__threadPool[i].join();
			__threadPool.pop_back();
			__threadState.pop_back();
		}
	}
}

void adv::cCore::addThread(function<void(int id, cArgs args)> target, cArgs args)
{
	int threadId = __threadPool.size();
	__threadState.push_back(STATE_UP);
	__threadPool.push_back(thread(target, threadId, args));
}

void adv::cCore::stopThread(int id)
{
	__threadState[id] = STATE_DOWN;
}

bool adv::cCore::isThreadGood(int id)
{
	return __threadState[id] == STATE_UP;
}

void adv::cCore::mainLoop()
{
	while (!__shutdownInitiated) {
		Sleep(10);
	}
}

void adv::cCore::exit()
{
	__shutdownInitiated = true;
}