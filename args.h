
#pragma once

#include "stdafx.h"

using namespace std;

namespace adv
{
	/*
	// Event arguments. Contains data about the object that has created the event or the conditions of said event.
	*/
	class cEventArgs
	{
	public:
		int id = -1;
		string name = "";
		vec2i posI;					// Can't be part of the condition
		vec2f posF;					// Can't be part of the condition
		int timer_tickTime;			// Can't be part of the condition
		float timer_tickDelay;		// Can't be part of the condition

		cEventArgs() {}
		cEventArgs(int id) { this->id = id; }
		cEventArgs(char* name) { this->name = name; }
		cEventArgs(string name) { this->name = name; }
		cEventArgs(int id, char* name) { this->id = id; this->name = name; }
		cEventArgs(int id, string name) { this->id = id; this->name = name; }
		cEventArgs(int id, vec2i posI) { this->id = id; this->posI = posI; }
		cEventArgs(int id, vec2f posF) { this->id = id; this->posF = posF; }
	};
}