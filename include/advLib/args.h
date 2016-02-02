
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
		/*
		// For mouse click events: Mouse button id
		// For UI button events: Mouse button id
		// For keyboard events: Key id
		// For input wrong events: Wrong character id
		// For timer events: Timer id (number)
		*/
		int id = -1;
		/*
		// For UI button events: Button name
		// For input events: Current input id
		// For timer events: Timer id (string)
		*/
		string name = "";
		/*
		// For mouse events: Mouse position
		*/
		vec2i posI;
		/*
		// For mouse events: Mouse position
		*/
		vec2f posF;
		/*
		// For timers: Expected tick time. No override.
		*/
		int timer_tickTime;
		/*
		// For timers: Real tick time. No override.
		*/
		float timer_tickDelay;

		// Any user-defined data.
		int user_int[8];
		// Any user-defined data.
		float user_float[8];
		// Any user-defined data.
		string user_string[8];

		cEventArgs() {}
		cEventArgs(int id) { this->id = id; }
		cEventArgs(char* name) { this->name = name; }
		cEventArgs(string name) { this->name = name; }
		cEventArgs(int id, char* name) { this->id = id; this->name = name; }
		cEventArgs(int id, string name) { this->id = id; this->name = name; }
		cEventArgs(int id, vec2i posI) { this->id = id; this->posI = posI; this->posF = vec2f((float)posI.x, (float)posI.y); }
		cEventArgs(int id, vec2f posF) { this->id = id; this->posF = posF; this->posI = vec2i((int)posF.x, (int)posF.y); }
	};

	class cTimerArgs
	{
	public:
		int id = -1;
		string name = "";

		cTimerArgs() {}
		cTimerArgs(int id) { this->id = id; }
		cTimerArgs(char* name) { this->name = name; }
	};
}