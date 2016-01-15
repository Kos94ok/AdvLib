
#include "stdafx.h"
#include "ui.h"

adv::cUIMain advUI;

void adv::cUIMain::init()
{
	desktopSize = vec2f((float)sf::VideoMode::getDesktopMode().width, (float)sf::VideoMode::getDesktopMode().height);

	advCore.addThread(threadUIMain, NULL);
	advUI.__root = true;
}

adv::cUIWindow* adv::cUIParent::addWindow(string id, vec2f pos, vec2f size, int align)
{
	cUIWindow newWindow;
	newWindow.id = id;

	newWindow.size = size;
	vec2f origin;
	if (align & ALIGN_CENTER) { origin.x = size.x / 2; }
	else if (align & ALIGN_RIGHT) { origin.x = size.x; }
	if (align & ALIGN_MID) { origin.y = size.y / 2; }
	else if (align & ALIGN_BOT) { origin.y = size.y; }
	newWindow.pos = this->pos + pos - origin;

	__childWindow.push_back(newWindow);
	return &__childWindow[(int)__childWindow.size() - 1];
}

adv::cUIWindow* adv::cUIParent::getWindow(string id)
{
	// First check all the owned windows
	for (int i = 0; i < (int)__childWindow.size(); i++) {
		if (__childWindow[i].id == id) { return &__childWindow[i]; }
	}
	// If not found, then we need to go deeper
	for (int i = 0; i < (int)__childWindow.size(); i++) {
		cUIWindow* val = __childWindow[i].getWindow(id);
		if (val != nullptr) { return val; }
	}
	if (__root) { advException.crash(CRASH::BADUIWINDOWID, id); }
	return nullptr;
}

void adv::cUIParent::moveChildWindow(string id, vec2f newPos)
{
	cUIWindow* wnd = getWindow(id);
	vec2f offset = newPos - wnd->pos;
	wnd->move(offset);
}

void adv::cUIWindow::move(vec2f offset)
{
	pos += offset;

	for (int i = 0; i < (int)__childElement.size(); i++) {
		__childElement[i].move(offset);
	}
	for (int i = 0; i < (int)__childWindow.size(); i++) {
		__childWindow[i].move(offset);
	}
}