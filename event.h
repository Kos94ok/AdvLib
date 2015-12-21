
#include "core.h"
#include "args.h"

#define FAMILY_GENERIC					1000
#define FAMILY_INTERFACE				1001
#define FAMILY_POST						1002

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
		int family;
	};

	/*
	// Event listener class.
	Internal use only.
	*/
	class cEventListener
	{
	public:
		cEvent event;
		cEventArgs condition;
		function<void(cEventArgs args)> handler;
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
		bool checkMatch(cEventArgs args, cEventArgs cond);
	public:
		/*
		// Initialize the event system. This function must be called during the main initialization.
		*/
		void init();
		/*
		// Create new event. If there are any eligible listeners, handlers will be executed as soon
		as there are free resources available.
		*/
		void add(int id, cEventArgs args = -1, int family = FAMILY_GENERIC);
		/*
		// Create a new event listener. Handler function will be executed as soon as there is a new
		event that matches 'id' and 'family', but only if the arguments of the event match the given
		conditions. Listener can't be removed from the list.
		Use 'id = -1' to match any event with specific family.
		*/
		void listen(int id, function<void(cEventArgs args)> handler, cEventArgs cond = -1, int family = FAMILY_GENERIC);
		/*
		// Blocks the thread until specific event occures.
		Use 'id = -1' to match any event with specific family.
		*/
		void waitFor(int id, int family = FAMILY_GENERIC);
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