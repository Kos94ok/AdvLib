
#include "stdafx.h"
#include "ui.h"

int adv::cUIMain::addFont(string id, string filename, int size)
{
	cUIFont font;

	font.id = id;
	font.size = size;
	bool isValid = font.handle.loadFromFile(advValue.path_fonts + filename);

	if (isValid) {
		this->__font.push_back(font);
		return this->__font.size() - 1;
	}
	else { return MISSINGNO; }
}

int adv::cUIMain::getFontIndex(string id)
{
	for (int i = 0; i < (int)__font.size(); i++) {
		if (__font[i].id == id) { return i; }
	}
	return MISSINGNO;
}

bool adv::cUIMain::_isFontValid(int index)
{
	return (index >= 0 && index < (int)__font.size() && __font[index].isValid);
}

adv::cUIFont* adv::cUIMain::getFont(int index)
{
	return &__font[index];
}