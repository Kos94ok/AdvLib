
#pragma once

#include "core.h"

#define LIMIT_FLAGS			128

namespace adv
{
	class cFlags
	{
	private:
		bool flag[LIMIT_FLAGS];
	public:
		void addFlag(int id) { flag[id] = true; }
		void removeFlag(int id) { flag[id] = false; }
		bool hasFlag(int id) { return flag[id]; }
		cFlags getFlags() { return *this; }

		cFlags()
		{
			for (int i = 0; i < LIMIT_FLAGS; i++) flag[i] = false;
		}
	};
}