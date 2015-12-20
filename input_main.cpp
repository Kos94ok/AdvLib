
#include "stdafx.h"
#include "input.h"

adv::cInputMain advInput;

bool adv::cInputMain::add(int character)
{
	if (!enabled) { return false; }

	if (isCharValid(character)) {
		wchar_t wchar = character;
		mainBuf += wchar;
		return true;
	}
	else {
		return false;
	}
}

void adv::cInputMain::add(wstring str)
{
	mainBuf.append(str);
}

wstring adv::cInputMain::getString()
{
	return mainBuf;
}

void adv::cInputMain::open(string id, int allowed)
{
	this->id = id;
	validCharset = allowed;
	enabled = true;
}

void adv::cInputMain::close(bool clearBuffer)
{
	if (clearBuffer) { clear(); }
	id = "";
	enabled = false;
}

void adv::cInputMain::clear()
{
	mainBuf.clear();
}

bool adv::cInputMain::isCharValid(int val)
{
	if (validCharset == INPUT_ANY) { return true; }
	else if (val == 32 && validCharset & INPUT_SPACE) { return true; }
	else if (val >= 97 && val <= 122 && validCharset & INPUT_LATIN) { return true; }
	else if (val >= 65 && val <= 90 && validCharset & INPUT_LATIN) { return true; }
	else if (val >= 1072 && val <= 1103 && validCharset & INPUT_CYRILLIC) { return true; }
	else if (val >= 1040 && val <= 1071 && validCharset & INPUT_CYRILLIC) { return true; }
	else if (val >= 48 && val <= 57 && validCharset & INPUT_NUMBERS) { return true; }
	else if (val >= 32 && val <= 47 && validCharset & INPUT_SPECIAL) { return true; }
	else if (val >= 58 && val <= 64 && validCharset & INPUT_SPECIAL) { return true; }
	else if (val >= 91 && val <= 96 && validCharset & INPUT_SPECIAL) { return true; }
	else if (val >= 123 && val <= 126 && validCharset & INPUT_SPECIAL) { return true; }

	return false;
}