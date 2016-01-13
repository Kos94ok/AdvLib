
#include "header.h"
#include "ui.h"

int adv::cUIMain::getHoveredButtonCount() {
	return (int)__hoveredUIButtons.size();
}
int adv::cUIMain::getPressedButtonCount() {
	return (int)__pressedUIButtons.size();
}
vector<adv::cUIElement*> adv::cUIMain::findHoveredButtons() {
	return __hoveredUIButtons;
}
vector<adv::cUIElement*> adv::cUIMain::findPressedButtons() {
	return __pressedUIButtons;
}

vector<adv::cUIElement*> adv::cUIMain::findByPoint(vec2f point, int type, int flags)
{
	vector<adv::cUIElement*> retArray;
	for (int i = 0; i < (int)__childWindow.size(); i++) {
		vector<adv::cUIElement*> smallArray = __childWindow[i].findByPoint(point, type, flags);
		retArray.insert(retArray.end(), smallArray.begin(), smallArray.end());
	}
	return retArray;
}

vector<adv::cUIElement*> adv::cUIWindow::findByPoint(vec2f point, int type, int flags)
{
	vector<adv::cUIElement*> retArray;
	for (int i = 0; i < (int)__childWindow.size(); i++) {
		vector<adv::cUIElement*> smallArray = __childWindow[i].findByPoint(point, type, flags);
		retArray.insert(retArray.end(), smallArray.begin(), smallArray.end());
	}
	for (int i = 0; i < (int)__childElement.size(); i++) {
		if (__childElement[i].type == type && advMath.isPointInRect(point.x + __childElement[i].center().x, point.y + __childElement[i].center().y,
			__childElement[i].pos().x, __childElement[i].pos().y, __childElement[i].size().x, __childElement[i].size().y)
			&& (!(flags & FND_EX_HIDDEN) || __childElement[i].isShown()))
		{
			retArray.push_back(&__childElement[i]);
		}
	}
	return retArray;
}

vector<adv::cUIElement*> adv::cUIMain::findById(string id, int type, int flags)
{
	vector<adv::cUIElement*> retArray;
	for (int i = 0; i < (int)__childWindow.size(); i++) {
		vector<adv::cUIElement*> smallArray = __childWindow[i].findById(id, type, flags);
		retArray.insert(retArray.end(), smallArray.begin(), smallArray.end());
	}
	return retArray;
}

vector<adv::cUIElement*> adv::cUIWindow::findById(string id, int type, int flags)
{
	vector<adv::cUIElement*> retArray;
	for (int i = 0; i < (int)__childWindow.size(); i++) {
		vector<adv::cUIElement*> smallArray = __childWindow[i].findById(id, type, flags);
		retArray.insert(retArray.end(), smallArray.begin(), smallArray.end());
	}
	for (int i = 0; i < (int)__childElement.size(); i++) {
		if (__childElement[i].type == type && __childElement[i].id == id
			&& (!(flags & FND_EX_HIDDEN) || __childElement[i].isShown()))
		{
			retArray.push_back(&__childElement[i]);
		}
	}
	return retArray;
}

vector<adv::cUIElement*> adv::cUIMain::findByName(string name, int type, int flags)
{
	vector<adv::cUIElement*> retArray;
	for (int i = 0; i < (int)__childWindow.size(); i++) {
		vector<adv::cUIElement*> smallArray = __childWindow[i].findByName(name, type, flags);
		retArray.insert(retArray.end(), smallArray.begin(), smallArray.end());
	}
	return retArray;
}

vector<adv::cUIElement*> adv::cUIWindow::findByName(string name, int type, int flags)
{
	vector<adv::cUIElement*> retArray;
	for (int i = 0; i < (int)__childWindow.size(); i++) {
		vector<adv::cUIElement*> smallArray = __childWindow[i].findByName(name, type);
		retArray.insert(retArray.end(), smallArray.begin(), smallArray.end());
	}
	for (int i = 0; i < (int)__childElement.size(); i++) {
		if (__childElement[i].type == type && __childElement[i].getButtonName() == name
			&& (!(flags & FND_EX_HIDDEN) || __childElement[i].isShown()))
		{
			retArray.push_back(&__childElement[i]);
		}
	}
	return retArray;
}