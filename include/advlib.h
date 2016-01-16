
#pragma once

//======================================================================================================================================================================
/* [Adventure Library | advLib]
// General notice
// 16.01.2016
- advLib was not designed to be used by other people. Included functionality may be too specific for general use, but that was the intent.
- Member functions and data fields marked with '_' or '__' are considered to only be used internally. Incorrect usage can cause undefined behaviour.
- Parts of the library are independant from each other and can be used separately. You don't have to use everything provided by advLib, if you don't need it.
- Some part is considered a subsystem if it requires initialization (and a separate thread) to operate. APIs don't require anything special to be used.
//======================================================================================================================================================================
// advCore | core.h: Essential part of the library. Handles initialization, multithreading and contains some support information.
Initialization and shutdown:
- init(): Initializes the subsystems. Should be called before using events or timers.
- postInit(): Performs post-init check. Should be called after advLib and user initialization has been completed.
- mainLoop(): Starts the main cycle. Should be called in main after all the threads have been started, although can be replaced by other type of main cycle.
- exit(): Start a shutdown process and returns from main loop. Called automatically on window close.
- shut(): Shutdowns all the threads. Should be called before returning from main.

Multithreading functions:
- addThread(...): Create a new thread. New thread must check for advCore.isThreadGood(id). If returned false - thread must be shutdown immediately.
- stopThread(...): Mark the thread as stopped. Must be executed right before returning from the thread function.
- isThreadGood(...): Check if the thread is good for running or should be stopped.
*/
#include <advLib/core.h>
//======================================================================================================================================================================
/* advEvent | event.h: First core subsystem. Responsible for advLib events and handlers, and also for translating SFML events into advLib events.
Initialization:
- init(): Initializes the system. Should be called before using any other functionality. Included in advCore.init().
Using events:
- add(...): Create a new event. If there are any eligible listeners, handlers will be executed as soon as there are free resources available.
			Reserved event IDs are [1000; 2999], any other values are considered custom events.
- listen(...): Create a new event listener. Event handler is executed as soon as possible after event with matching ID has occured. Event listeners can't be destroyed.
- listenForTimer(...): Create a new timer event listener. Event handler is executed as soon as possible after EVENT_TIMER_TICK with matching timer id has occured.
- waitFor(...): Blocks the thread execution until a specific event. In case multiple events happen simultaneously, returning from the function is not guaranteed.
- handle(...): Take care of an SFML event. Those events should be polled from SFML window, checked for user events, and, if nothing matched, given to advLib.
*/
#include <advLib/event.h>
//======================================================================================================================================================================
/* advTimer | timer.h: Second core subsystem. Responsible for creating and handling of static and dynamic timers.
Initialization:
- init(): Initializes the system. Should be called before using any other functionality. Included in advCore.init().
Using timers:
- start(...): Create a static timer. This timer can not be destroyed and only one instance is allowed. This timer is intended to be used as a global constant timer.
- startFor(...): Start a dynamic timer. Dynamic timers have a limited life. Those are intended to be used for temporary effects' logic.
*/
#include <advLib/timer.h>
//======================================================================================================================================================================
/*
// Not documented part
*/
#include <advLib/drawable.h>
//======================================================================================================================================================================
#include <advLib/animation.h>
//======================================================================================================================================================================
#include <advLib/texture.h>
//======================================================================================================================================================================
#include <advLib/mouse.h>
//======================================================================================================================================================================
#include <advLib/ui.h>
//======================================================================================================================================================================
#include <advLib/vectox.h>
//======================================================================================================================================================================
#include <advLib/input.h>
//======================================================================================================================================================================
#include <advLib/database.h>
//======================================================================================================================================================================