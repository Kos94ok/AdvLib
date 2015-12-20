
#include "stdafx.h"
#include "event.h"

void adv::cEventMain::__threadMain(int id, cArgs args)
{
	advCore.threadState[id] = STATE_UP;
	//cout << "Thread " << id << " is now up" << endl;
	function<void(cEventArgs args)> queueFunc;
	cEventArgs queueArgs;
	do
	{
		// Lock the queue
		advEvent.__getHandlerQueue()->access.lock();
		// Check, if something is present
		if (advEvent.__getHandlerQueue()->list.size() > 0)
		{
			// If something is present, pick first function to be executed
			queueFunc = advEvent.__getHandlerQueue()->list[0];
			queueArgs = advEvent.__getHandlerQueue()->args[0];
			// Remove the function from the queue
			advEvent.__getHandlerQueue()->removeFirst();
			// Unlock the queue
			advEvent.__getHandlerQueue()->access.unlock();
			// Execute
			queueFunc(queueArgs);
		}
		else {
			// Otherwise, unlock the queue...
			advEvent.__getHandlerQueue()->access.unlock();
			// ...and go to sleep
			Sleep(1);
		}
	} while (advCore.isThreadGood(id));
	//cout << "Thread " << id << " is now down" << endl;
	advCore.threadState[id] = STATE_DOWN;
}