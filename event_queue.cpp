
#include "stdafx.h"
#include "event.h"

void adv::cHandlerQueue::add(function<void(cEventArgs args)> handler, cEventArgs args)
{
	access.lock();

	list.push_back(handler);
	this->args.push_back(args);

	access.unlock();
}

void adv::cHandlerQueue::removeFirst()
{
	list.erase(list.begin(), list.begin() + 1);
	args.erase(args.begin(), args.begin() + 1);
}