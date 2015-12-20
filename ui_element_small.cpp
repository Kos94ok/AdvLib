
#include "stdafx.h"
#include "ui.h"

void adv::cUIWindow::showElement(string id, int type, bbool val) {
	cUIElement* elem = _getElement(id, type);
	if (elem != nullptr) { elem->show(val); }
}

void adv::cUIWindow::setLabelPos(string id, vec2f newPos) {
	cUIElement* elem = _getElement(id, TYPE_LABEL);
	if (elem != nullptr) { elem->moveto(pos + newPos); }
}

void adv::cUIWindow::setLabelText(string id, wstring text) {
	cUIElement* elem = _getElement(id, TYPE_LABEL);
	if (elem != nullptr) { elem->setLabelText(text); }
}

void adv::cUIWindow::setLabelColor(string id, color clr) {
	cUIElement* elem = _getElement(id, TYPE_LABEL);
	if (elem != nullptr) { elem->setLabelColor(clr); }
}

void adv::cUIWindow::setLabelFont(string id, int fontIndex) {
	cUIElement* elem = _getElement(id, TYPE_LABEL);
	if (elem != nullptr) { elem->setLabelFont(fontIndex); }
}

void adv::cUIWindow::setLabelAlign(string id, int align) {
	cUIElement* elem = _getElement(id, TYPE_LABEL);
	if (elem != nullptr) { elem->setLabelAlign(align); }
}

void adv::cUIWindow::setButtonPos(string id, vec2f newPos) {
	cUIElement* elem = _getElement(id, TYPE_BUTTON);
	if (elem != nullptr) { elem->moveto(pos + newPos); }
}

void adv::cUIWindow::setButtonSize(string id, vec2f newSize) {
	cUIElement* elem = _getElement(id, TYPE_BUTTON);
	if (elem != nullptr) { elem->resize(newSize); }
}

void adv::cUIWindow::setButtonName(string id, string name) {
	cUIElement* elem = _getElement(id, TYPE_BUTTON);
	if (elem != nullptr) { elem->setButtonName(name); }
}

void adv::cUIWindow::setButtonAlign(string id, int align) {
	cUIElement* elem = _getElement(id, TYPE_BUTTON);
	if (elem != nullptr) { elem->setButtonAlign(align); }
}

void adv::cUIWindow::setButtonTexture(string id, int tex) {
	cUIElement* elem = _getElement(id, TYPE_BUTTON);
	if (elem != nullptr) { elem->setImageTexture(tex); }
}

void adv::cUIWindow::setButtonTextString(string id, wstring text) {
	cUIElement* elem = _getElement(id, TYPE_BUTTON);
	if (elem != nullptr) { elem->setLabelText(text); }
}

void adv::cUIWindow::setButtonTextColor(string id, color clr) {
	cUIElement* elem = _getElement(id, TYPE_BUTTON);
	if (elem != nullptr) { elem->setLabelColor(clr); }
}

void adv::cUIWindow::setButtonTextFont(string id, int fontIndex) {
	cUIElement* elem = _getElement(id, TYPE_BUTTON);
	if (elem != nullptr) { elem->setLabelFont(fontIndex); }
}

void adv::cUIWindow::setButtonTextAlign(string id, int align) {
	cUIElement* elem = _getElement(id, TYPE_BUTTON);
	if (elem != nullptr) { elem->setLabelAlign(align); }
}

void adv::cUIWindow::setButtonHoverTexture(string id, int tex) {
	cUIElement* elem = _getElement(id, TYPE_BUTTON);
	if (elem != nullptr) { elem->setButtonHoverTexture(tex); }
}

void adv::cUIWindow::setButtonHoverFadeTime(string id, float time) {
	cUIElement* elem = _getElement(id, TYPE_BUTTON);
	if (elem != nullptr) { elem->setButtonFadeMax(time); }
}

void adv::cUIWindow::setButtonHoverTextColor(string id, color clr) {
	cUIElement* elem = _getElement(id, TYPE_BUTTON);
	if (elem != nullptr) { elem->setButtonHoverTextColor(clr); }
}
