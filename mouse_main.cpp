
#include "stdafx.h"
#include "mouse.h"
#include "event.h"
#include "drawable.h"

using namespace adv;

adv::cMouseMain advMouse;

void adv::cMouseMain::dragObject(cDrawable* obj, vec2f anchor, int align)
{
	// Update anchor
	if (align == ALIGN_AUTO) {
		anchor = obj->pos() + obj->center() - posF;
	}
	else {
		if (align & ALIGN_LEFT) { anchor.x += obj->center().x; }
		//else if (align & ALIGN_CENTER) { anchor.x += obj->pos().x - posF.x; }
		else if (align & ALIGN_RIGHT) { anchor.x += obj->center().x - obj->size().x; }
		if (align & ALIGN_TOP) { anchor.y += obj->center().y; }
		//else if (align & ALIGN_MID) { anchor.y += obj->pos().y - posF.y; }
		else if (align & ALIGN_BOT) { anchor.y += obj->center().y - obj->size().y; }
	}

	dragList.push_back(obj);
	dragAnchorList.push_back(anchor);

	__updateDraggedObjects();
}

void adv::cMouseMain::dropObject(cDrawable* obj)
{
	for (int i = 0; i < (int)dragList.size(); i++) {
		if (dragList[i] == obj) {
			dragList.erase(dragList.begin() + i, dragList.begin() + i + 1);
			dragAnchorList.erase(dragAnchorList.begin() + i, dragAnchorList.begin() + i + 1);
			i -= 1;
		}
	}
}

void adv::cMouseMain::dropAll()
{
	dragList.clear();
	dragAnchorList.clear();
}

void adv::cMouseMain::__init()
{
	advEvent.listen(EVENT_MOUSE_MOVE, __listener_dataUpdate);
}

void adv::cMouseMain::__listener_dataUpdate(cEventArgs args)
{
	advMouse.pos = args.posI;
	advMouse.posF = vec2f((float)advMouse.pos.x, (float)advMouse.pos.y);

	// Moving dragged objects
	advMouse.__updateDraggedObjects();
}

void adv::cMouseMain::__updateDraggedObjects()
{
	for (int i = 0; i < (int)dragList.size(); i++) {
		dragList[i]->moveto(posF + dragAnchorList[i]);
	}
}