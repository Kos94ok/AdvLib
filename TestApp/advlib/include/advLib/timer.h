
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
	/*
	// Timer data class.
	Internal use only.
	*/
	class cTimer
	{
	public:
		int id = MISSINGNO;
		string name = "";
		int tickTime = 0;
		float timeCur = 0.00f;
		float timeMax = 0.00f;
		cEventArgs tickArgs;
	};

	class cTimerDynamic
	{
	public:
		int ttl = 1;
		int tickTime = 0;
		float timeCur = 0.00f;
		float timeMax = 0.00f;
		cEventArgs tickArgs;
		function<void(cEventArgs args)> tickHandler;
	};

	/*
	// Main timer system class.
	*/
	class cTimerMain
	{
	private:
		sf::Mutex __access;
		bool __initialized = false;
		vector<cTimer> __timerList;
		vector<cTimerDynamic> __timerDynamicList;
	public:
		/*
		// Initialize the system. Must be called before using any timers.
		*/
		void init();
		/*
		// Start a static timer. This timer can not be destroyed and only one instance is allowed. Use advEvent.listenForTimer(...).
		This timer is intended to be used as a global constant timer, responsible for main logic.
		*/
		void start(float time, cTimerArgs args);
		/*
		// Start a dynamic timer. This timer expires when TTL == 0. Every tick removes one TTL token.
		This timer is intended to be used for characters' abilities or other similar kind of temporary effects' logic.
		'args' field will be given to the event handler as is.
		*/
		void startFor(float time, function<void(cEventArgs args)> entryFunc, int ttl = 1, cEventArgs args = -1);

		void _removeTimer(int number);
		void _removeTimerDynamic(int number);
		int _getTimerCount() { return __timerList.size(); }
		int _getTimerDynamicCount() { return __timerDynamicList.size(); }
		cTimer* _getTimerHandle(int number) { return &__timerList[number]; }
		cTimerDynamic* _getTimerDynamicHandle(int number) { return &__timerDynamicList[number]; }

		/*
		// Internal use only.
		Main thread function.
		*/
		static void __threadMain(int id, cArgs args);
	};
}

extern adv::cTimerMain advTimer;