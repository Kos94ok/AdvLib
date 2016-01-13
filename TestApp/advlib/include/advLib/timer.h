
#include "core.h"

#define TIMER_10MS					1000
#define TIMER_50MS					1001
#define TIMER_100MS					1002
#define TIMER_300MS					1003
#define TIMER_500MS					1004
#define TIMER_1000MS				1005
#define TIMER_2000MS				1006
#define TIMER_5000MS				1007

namespace adv
{
	class cTimerArgs
	{
	public:
		int id = -1;
		string name = "";

		cTimerArgs() {}
		cTimerArgs(int id) { this->id = id; }
		cTimerArgs(char* name) { this->name = name; }
	};

	/*
	// Timer data class.
	Internal use only.
	*/
	class cTimer
	{
	public:
		int id = -1;
		string name = "";
		bool repeat = false;
		float timeCur = 0.00f;
		float timeMax = 0.00f;
		int tickTime = 0;
	};

	/*
	// Main timer system class.
	*/
	class cTimerMain
	{
	private:
		sf::Mutex access;
		bool initialized = false;
		vector<cTimer> timerList;
	public:
		void init();
		void start(float time, cTimerArgs args, bool repeat = false);

		void __removeTimer(int number);
		int __getTimerCount() { return timerList.size(); }
		cTimer* __getTimerHandle(int number) { return &timerList[number]; }

		/*
		// Internal use only.
		Main thread function.
		*/
		static void __threadMain(int id, cArgs args);
	};
}

extern adv::cTimerMain advTimer;