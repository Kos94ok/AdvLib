
#include "core.h"
#include "align.h"
#include "args.h"

namespace adv
{
	class cDrawable;

	class cMouseMain
	{
	private:
		void __updateDraggedObjects();
	public:
		vec2i pos;
		vec2f posF;

		vector<cDrawable*> dragList;
		vector<vec2f> dragAnchorList;

		/*
		// Attach a drawable object to the mouse.
		*/
		void dragObject(cDrawable* obj, vec2f anchor = vec2f(0.f, 0.f), int align = ALIGN_AUTO);
		/*
		// Drop a dragged object.
		*/
		void dropObject(cDrawable* obj);
		/*
		// Drop all dragged objects.
		*/
		void dropAll();

		/*
		// Internal use only.
		Initialize the mouse subsystem.
		*/
		void __init();
		/*
		// Internal use only.
		Mouse event listener.
		*/
		static void __listener_dataUpdate(cEventArgs args);
	};
}

extern adv::cMouseMain advMouse;