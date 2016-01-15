
#include "stdafx.h"
#include "ui.h"

adv::cUIElement* adv::cUIWindow::_getElement(string id, int type)
{
	for (int i = 0; i < (int)__childElement.size(); i++) {
		if (__childElement[i].type == type && __childElement[i].id == id) { return &__childElement[i]; }
	}
	return nullptr;
}

void adv::cUIWindow::addImage(string id, vec2f pos, vec2f size, int tex, int align)
{
	cUIElement newElement;
	newElement.id = id;

	// Initialize the element
	newElement.type = TYPE_IMAGE;
	newElement.setImageTexture(tex);
	newElement.setImageAlign(align);
	newElement.moveto(this->pos + pos);
	newElement.resize(size);
	// Push to vector
	__childElement.push_back(newElement);
}

void adv::cUIWindow::addLabel(string id, vec2f pos, wstring text, string fontId, color clr, int align)
{
	cUIElement newElement;
	newElement.id = id;

	// Check the font
	if (advUI.getFontIndex(fontId) == MISSINGNO) {
		advException.crash(CRASH_BADFONTID, fontId);
		return;
	}
	// Initialize the element
	newElement.type = TYPE_LABEL;
	newElement.setLabelText(text);
	newElement.setLabelColor(clr);
	newElement.setLabelAlign(align);
	newElement.setLabelFont(advUI.getFontIndex(fontId));
	newElement.moveto(this->pos + pos);
	// Push to vector
	__childElement.push_back(newElement);
}

void adv::cUIWindow::addButton(string id, vec2f pos, vec2f size, string name, int bgTex, int align)
{
	cUIElement newElement;
	newElement.id = id;

	// Initialize the element
	newElement.type = TYPE_BUTTON;
	newElement.moveto(this->pos + pos);
	newElement.resize(size);
	newElement.setImageTexture(bgTex);
	newElement.setButtonName(name);
	newElement.setButtonAlign(align);
	newElement.setButtonFadeMax(1.f);
	// Calculate the origin
	vec2f origin;
	if (align & ALIGN_CENTER) { origin.x = (float)advMath.round(size.x / 2.00f); }
	else if (align & ALIGN_RIGHT) { origin.x = (float)advMath.round(size.x); }
	if (align & ALIGN_MID) { origin.y = (float)advMath.round(size.y / 2.00f); }
	else if (align & ALIGN_BOT) { origin.y = (float)advMath.round(size.y); }
	newElement.centralize(origin);
	// Push to vector
	__childElement.push_back(newElement);
}

void adv::cUIWindow::addButtonText(string id, wstring text, string fontId, color clr, int align)
{
	if (advUI.getFontIndex(fontId) == MISSINGNO) {
		advException.crash(CRASH_BADFONTID, fontId);
		return;
	}
	setButtonTextString(id, text);
	setButtonTextFont(id, advUI.getFontIndex(fontId));
	setButtonTextColor(id, clr);
	setButtonTextAlign(id, align);
}

void adv::cUIWindow::addButtonHover(string id, int tex, float time, color textColor)
{
	setButtonHoverTexture(id, tex);
	setButtonHoverFadeTime(id, time);
	setButtonHoverTextColor(id, textColor);
}