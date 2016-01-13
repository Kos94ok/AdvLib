
#include "header.h"
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
	int threadCount = threadPool.size();
	// Checking all the threads in reverse order
	for (int i = threadCount - 1; i >= 0; i--) {
		if (threadState[i] == STATE_UP) {
			threadState[i] = STATE_SHUTTING;
			threadPool[i].join();
			threadPool.pop_back();
			threadState.pop_back();
		}
	}
}

void adv::cCore::addThread(function<void(int id, cArgs args)> target, cArgs args)
{
	int threadId = advCore.threadPool.size();
	advCore.threadState.push_back(STATE_DOWN);
	advCore.threadPool.push_back(thread(target, threadId, args));
}

bool adv::cCore::isThreadGood(int id)
{
	return threadState[id] == STATE_UP;
}

void adv::cCore::mainLoop()
{
	while (!shutdownInitiated) {
		Sleep(10);
	}
}

void adv::cCore::exit()
{
	shutdownInitiated = true;
}