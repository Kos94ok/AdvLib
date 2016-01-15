
#include "stdafx.h"
#include "event.h"

adv::cEventMain advEvent;

void adv::cEventMain::init()
{
	if (initialized) { return; }
	initialized = true;

	for (int i = 0; i < advValue.count_eventHandlers; i++) { advCore.addThread(__threadMain, 0); }
}

void adv::cEventMain::add(int id, cEventArgs args, int family)
{
	latest.id = id;
	latest.family = family;
	// Check all the listeners
	for (cEventListener ear : listenerList)
	{
		if (ear.event.id == id && ear.event.family == family && checkMatch(args, ear.condition))
		{
			// If something is listening to new event, execute the event handlers - each in separate thread
			handlerQueue.add(ear.handler, args);
		}
	}
}

void adv::cEventMain::listen(int id, function<void(cEventArgs args)> handler, cEventArgs cond, int family)
{
	// Check for duplicates
	for (int i = 0; i < (int)listenerList.size(); i++) {
		if (listenerList[i].event.id == id && listenerList[i].event.family == family && checkMatch(listenerList[i].condition, cond)
			&& !checkMatch(cond, cEventArgs()))
		{
			advException.warning(WARNING::DUPLISTENER, to_string(id) + " | " + to_string(family) + " | " + to_string(cond.id) + " | " + cond.name);
			return;
		}
	}
	// Add new
	cEventListener ear;
	ear.event.id = id;
	ear.event.family = family;
	ear.handler = handler;
	ear.condition = cond;
	listenerList.push_back(ear);
}

void adv::cEventMain::waitFor(int id, int family)
{
	while (latest.id != id || latest.family != family) { Sleep(1); }
}

bool adv::cEventMain::checkMatch(cEventArgs args, cEventArgs cond)
{
	if (cond.id != -1 && args.id != cond.id) { return false; }
	if (cond.name != "" && args.name != cond.name) { return false; }
	return true;
}