
#pragma once

#include "stdafx.h"
#include "exception.h"
#include "advmath.h"
#include "align.h"
#include "args.h"
#include "bbool.h"
#include "const.h"
#include "other.h"
#include "flags.h"
#include "id.h"

#define STATE_UP				0			// Thread is working normally
#define STATE_DOWN				1			// Thread is disabled
#define STATE_SHUTTING			2			// Thread is shutting down

using namespace std;

namespace adv
{
	class cCore
	{
	private:
		bool __shutdownInitiated = false;
		vector<short> __threadState;
		vector<thread> __threadPool;
	public:
		/*
		// Initialize the core functions.
		*/
		void init();
		/*
		// Post-initialization. Should be called after all the systems have been initialized.
		*/
		void postInit();
		/*
		// Start the shutdown process. Must be executed right before returning from the main function.
		*/
		void shut();
		/*
		// Exit the main loop and start the shutdown process.
		*/
		void exit();
		/*
		// Create a new thread. Entry point function should be defined as follows:
		void name(int id, cArgs args);
		*/
		void addThread(function<void(int id, cArgs args)> target, cArgs args);
		/*
		// Check if the thread state is ok. If not, shutdown is required.
		*/
		bool isThreadGood(int id);
		/*
		// Mark the thread as shutdown.
		Must be called before returning from the thread function.
		*/
		void stopThread(int id);
		/*
		// Start the core main cycle. The thread is then blocked until the advCore.exit() function is called.
		Should only be executed from the main thread.
		*/
		void mainLoop();
		/*
		The core needs some tea as well sometimes.
		*/
		void teaBreak() { Sleep(3000); }
	};
}

extern adv::cCore advCore;