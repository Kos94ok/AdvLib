
#pragma once

/*
// core.h: Essential part of the library. Handles initialization, multithreading and contains some support information.
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

/*
// Not documented part
*/
#include <advLib/event.h>
#include <advLib/timer.h>
#include <advLib/drawable.h>
#include <advLib/animation.h>
#include <advLib/texture.h>
#include <advLib/mouse.h>
#include <advLib/ui.h>
#include <advLib/vectox.h>
#include <advLib/input.h>
#include <advLib/database.h>