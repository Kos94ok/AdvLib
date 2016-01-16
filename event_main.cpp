
#include "stdafx.h"
#include "event.h"

adv::cEventMain advEvent;

void adv::cEventMain::init()
{
	if (initialized) { return; }
	initialized = true;

	for (int i = 0; i < advValue.count_eventHandlers; i++) { advCore.addThread(__threadMain, 0); }
}

void adv::cEventMain::add(int id, cEventArgs args)
{
	cEventListener ear;
	latest.id = id;
	// Check all the listeners
	for (int i = 0; i < (int)listenerList.size(); i++)
	//for (cEventListener ear : listenerList)
	{
		ear = listenerList[i];
		if (ear.event.id == id && // <--- Generic condition
			(ear.timerCond.id == -1 || ear.timerCond.id == args.id) && (ear.timerCond.name == "" || ear.timerCond.name == args.name)) // <--- Timer condition
		{
			// If something is listening to new event, execute the event handlers
			handlerQueue.add(ear.handler, args);
		}
	}
}

void adv::cEventMain::listen(int id, function<void(cEventArgs args)> handler)
{
	cEventListener ear;
	ear.event.id = id;
	ear.handler = handler;
	listenerList.push_back(ear);
}

void adv::cEventMain::listenForTimer(cTimerArgs timer, function <void(cEventArgs args)> handler)
{
	cEventListener ear;
	ear.event.id = EVENT_TIMER_TICK;
	ear.handler = handler;
	ear.timerCond = timer;
	listenerList.push_back(ear);
}

void adv::cEventMain::waitFor(int id)
{
	while (latest.id != id) { Sleep(1); }
}
