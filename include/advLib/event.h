
#include "core.h"

// 1000 - L0 events
#define EVENT_INIT						1000
#define EVENT_TEST						1001
#define EVENT_PRESHUT					1002
#define EVENT_TIMER_START				1003
#define EVENT_TIMER_TICK				1004
#define EVENT_TIMER_END					1005
#define EVENT_MOUSE_PRESS				1006
#define EVENT_MOUSE_RELEASE				1007
#define EVENT_MOUSE_MOVE				1008
#define EVENT_KEY_PRESS					1009
#define EVENT_KEY_RELEASE				1010
#define EVENT_INPUT_UPDATE				1011
#define EVENT_INPUT_WRONG				1012

// 1100 - UI L1 events
#define EVENT_UIBTN_PRESS				1100
#define EVENT_UIBTN_RELEASE				1101
#define EVENT_NOBTN_PRESS				1102
#define EVENT_NOBTN_RELEASE				1103
#define EVENT_UIBTN_HOVER				1104
#define EVENT_UIBTN_NOHOVER				1105

namespace adv
{
	/*
	// Event data class. Contains data about occured event.
	*/
	class cEvent
	{
	public:
		int id;
	};

	/*
	// Event listener class.
	Internal use only.
	*/
	class cEventListener
	{
	public:
		cEvent event;
		function<void(cEventArgs args)> handler;
		int condition;

		cTimerArgs timerCond;
	};

	/*
	// Event handler queue class.
	Internal use only.
	*/
	class cHandlerQueue
	{
	public:
		sf::Mutex access;
		vector<cEventArgs> args;
		vector<function<void(cEventArgs args)>> list;

		void add(function<void(cEventArgs args)> handler, cEventArgs args);
		void removeFirst();
	};

	/*
	// Main event system class.
	*/
	class cEventMain
	{
	private:
		bool initialized = false;
		cEvent latest;

		vector<cEventListener> listenerList;
		cHandlerQueue handlerQueue;

		cEvent getLastEvent() { return latest; }
	public:
		/*
		// Initialize the event system. This function must be called during the main initialization.
		*/
		void init();
		/*
		// Create new event. If there are any eligible listeners, handlers will be executed as soon
		as there are free resources available.
		*/
		void add(int id, cEventArgs args = -1);
		/*
		// Create a new event listener. Handler function will be executed as soon as there is a new
		event that matches 'id' field. Listener can't be removed from the list. This function is intended
		to be used with global events that require similar reaction every time.
		*/
		void listen(int id, function<void(cEventArgs args)> handler, int condition = -1);
		/*
		// Create a new event listener. Handler function will be executed as soon as there is a new
		EVENT_TIMER_TICK event with matching timer IDs. Listener can't be removed from the list. This
		function is intended to be used with global timers that require similar reaction every time.
		*/
		void listenForTimer(cTimerArgs timer, function <void(cEventArgs args)> handler);
		/*
		// Blocks the thread until specific event occures.
		*/
		void waitFor(int id);
		/*
		// Handles generic SFML events.
		*/
		void handle(sf::Event eventPoll, sf::RenderWindow* winHandle);

		/*
		// Internal use only.
		Returns a pointer to 'handlerQueue' private object.
		*/
		cHandlerQueue* __getHandlerQueue() { return &handlerQueue; }

		/*
		// Internal use only.
		Main thread function.
		*/
		static void __threadMain(int id, cArgs args);
	};
}

extern adv::cEventMain advEvent;