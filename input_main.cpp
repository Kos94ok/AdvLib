
#include "stdafx.h"
#include "input.h"

adv::cInputMain advInput;

bool adv::cInputMain::add(int character)
{
	if (!_enabled) { return false; }

	if (__isCharValid(character)) {
		wchar_t wchar = character;
		_mainBuf[_caret.y].insert(_mainBuf[_caret.y].begin() + _caret.x, wchar);
		_caret.x += 1;
		_prefX = _caret.x;
		return true;
	}
	else {
		return false;
	}
}

void adv::cInputMain::add(wstring str)
{
	if (!_enabled) { return; }

	for (int i = 0; i < (int)str.length(); i++) {
		_mainBuf[_caret.y].insert(_mainBuf[_caret.y].begin() + _caret.x, str[i]);
		_caret.x += 1;
		_prefX = _caret.x;
	}
}

bool adv::cInputMain::addSpec(int key)
{
	if (!_enabled || !__isCharSpecial(key)) { return false; }

	// Enter
	if (key == sf::Keyboard::Return && _lineCount < _lineMax) {
		// Transferring bottom lines
		for (int i = _lineCount - 1; i > _caret.y; i--) {
			_mainBuf[i + 1] = _mainBuf[i];
		}
		// Transferring current line substring
		_mainBuf[_caret.y + 1] = _mainBuf[_caret.y].substr(_caret.x);
		_mainBuf[_caret.y] = _mainBuf[_caret.y].substr(0, _caret.x);
		// Updating caret pos
		_caret.x = 0;
		_caret.y += 1;
		_prefX = _caret.x;
		// Updating line count
		_lineCount += 1;
		return true;
	}
	// Delete (normal)
	else if (key == sf::Keyboard::Delete && _caret.x < (int)_mainBuf[_caret.y].length()) {
		_mainBuf[_caret.y].erase(_mainBuf[_caret.y].begin() + _caret.x, _mainBuf[_caret.y].begin() + _caret.x + 1);
		return true;
	}
	// Delete (line)
	else if (key == sf::Keyboard::Delete && _caret.x == (int)_mainBuf[_caret.y].length() && _caret.y < _lineCount - 1) {
		// Appending the strings
		_mainBuf[_caret.y] += _mainBuf[_caret.y + 1];
		// Moving the bottom lines
		for (int i = _caret.y + 1; i < _lineCount; i++) {
			_mainBuf[i] = _mainBuf[i + 1];
		}
		// Clearing the last line
		_mainBuf[_lineCount - 1].clear();
		// Updating line count
		_lineCount -= 1;
		return true;
	}
	// Backspace (normal)
	else if (key == sf::Keyboard::BackSpace && _caret.x > 0) {
		_mainBuf[_caret.y].erase(_mainBuf[_caret.y].begin() + _caret.x - 1, _mainBuf[_caret.y].begin() + _caret.x);
		_caret.x -= 1;
		_prefX = _caret.x;
		return true;
	}
	// Backspace (line)
	else if (key == sf::Keyboard::BackSpace && _caret.x == 0 && _caret.y > 0) {
		// Writing new pos for the caret
		int newPos = (int)_mainBuf[_caret.y - 1].length();
		// Appending the strings
		_mainBuf[_caret.y - 1] += _mainBuf[_caret.y];
		// Moving the bottom lines
		for (int i = _caret.y; i < _lineCount; i++) {
			_mainBuf[i] = _mainBuf[i + 1];
		}
		// Clearing the last line
		_mainBuf[_lineCount - 1].clear();
		// Updating the caret
		_caret.x = newPos;
		_caret.y -= 1;
		_prefX = _caret.x;
		// Updating line count
		_lineCount -= 1;
		return true;
	}
	// Up
	else if (key == sf::Keyboard::Up) {
		_caret.y -= 1;
		if (_caret.y < 0) { _caret.y = 0; }
		if (_prefX < (int)_mainBuf[_caret.y].length()) {
			_caret.x = _prefX;
		}
		else {
			_caret.x = (int)_mainBuf[_caret.y].length();
		}
		return true;
	}
	// Down
	else if (key == sf::Keyboard::Down) {
		_caret.y += 1;
		if (_caret.y >= _lineCount) { _caret.y = _lineCount - 1; }
		if (_prefX < (int)_mainBuf[_caret.y].length()) {
			_caret.x = _prefX;
		}
		else {
			_caret.x = (int)_mainBuf[_caret.y].length();
		}
		return true;
	}
	// Left
	else if (key == sf::Keyboard::Left) {
		if (_caret.x > 0) {
			_caret.x -= 1;
			if (_caret.x < 0) { _caret.x = 0; }
			_prefX = _caret.x;
		}
		else if (_caret.y > 0) {
			_caret.y -= 1;
			_caret.x = _mainBuf[_caret.y].length();
			_prefX = _caret.x;
		}
		return true;
	}
	// Right
	else if (key == sf::Keyboard::Right) {
		if (_caret.x < (int)_mainBuf[_caret.y].length()) {
			_caret.x += 1;
			_caret.x = min((int)_mainBuf[_caret.y].length(), _caret.x);
			_prefX = _caret.x;
		}
		else if (_caret.y < _lineCount - 1) {
			_caret.y += 1;
			_caret.x = 0;
			_prefX = _caret.x;
		}
		return true;
	}
	// Home
	else if (key == sf::Keyboard::Home) {
		_caret.x = 0;
		_prefX = _caret.x;
		return true;
	}
	// End
	else if (key == sf::Keyboard::End) {
		_caret.x = (int)_mainBuf[_caret.y].length();
		_prefX = _caret.x;
		return true;
	}
	// Page Up
	else if (key == sf::Keyboard::PageUp) {
		_caret.y = 0;
		if (_prefX < (int)_mainBuf[_caret.y].length()) {
			_caret.x = _prefX;
		}
		else {
			_caret.x = (int)_mainBuf[_caret.y].length();
		}
		return true;
	}
	// Page Down
	else if (key == sf::Keyboard::PageDown) {
		_caret.y = _lineCount - 1;
		if (_prefX < (int)_mainBuf[_caret.y].length()) {
			_caret.x = _prefX;
		}
		else {
			_caret.x = (int)_mainBuf[_caret.y].length();
		}
		return true;
	}
	return false;
}

wstring adv::cInputMain::getString(int index)
{
	index = max(0, min(LIMIT_INPUTLINES, index));

	return _mainBuf[index];
}

vec2f adv::cInputMain::getCaretPos(string fontId, int spacing, wstring prefix)
{
	int charSize = advUI.getFont(advUI.getFontIndex(fontId))->size;
	sf::Text text;
	text.setString(prefix + _mainBuf[_caret.y].substr(0, _caret.x));
	text.setFont(advUI.getFont(advUI.getFontIndex(fontId))->handle);
	text.setCharacterSize(charSize);
	return vec2f(text.getGlobalBounds().width + 1.f, _caret.y * ((float)charSize + spacing));
}

void adv::cInputMain::open(string id, int allowed, int lines, bool clearBuffer)
{
	if (clearBuffer) { clear(); }

	_id = id;
	_validCharset = allowed;
	_lineMax = min(lines, LIMIT_INPUTLINES);
	_enabled = true;
}

void adv::cInputMain::close(bool clearBuffer)
{
	if (clearBuffer) { clear(); }

	_enabled = false;
}

void adv::cInputMain::clear()
{
	_lineCount = 1;
	_caret = vec2i(0, 0);
	_prefX = _caret.x;
	for (int i = 0; i < LIMIT_INPUTLINES; i++) {
		_mainBuf[i].clear();
	}
}

bool adv::cInputMain::__isCharValid(int val)
{
	//cout << val << endl;

	// Block special characters
	if (val == 8 || val == 13) { return false; }
	// Then check the others
	if (_validCharset == INPUT_ANY) { return true; }
	else if (val == 32 && _validCharset & INPUT_SPACE) { return true; }
	else if (val >= 97 && val <= 122 && _validCharset & INPUT_LATIN) { return true; }
	else if (val >= 65 && val <= 90 && _validCharset & INPUT_LATIN) { return true; }
	else if (val >= 1072 && val <= 1103 && _validCharset & INPUT_CYRILLIC) { return true; }
	else if (val >= 1040 && val <= 1071 && _validCharset & INPUT_CYRILLIC) { return true; }
	else if (val >= 48 && val <= 57 && _validCharset & INPUT_NUMBERS) { return true; }
	else if (val >= 32 && val <= 47 && _validCharset & INPUT_SPECIAL) { return true; }
	else if (val >= 58 && val <= 64 && _validCharset & INPUT_SPECIAL) { return true; }
	else if (val >= 91 && val <= 96 && _validCharset & INPUT_SPECIAL) { return true; }
	else if (val >= 123 && val <= 126 && _validCharset & INPUT_SPECIAL) { return true; }

	return false;
}

bool adv::cInputMain::__isCharSpecial(int val)
{
	if (val == sf::Keyboard::Return) { return true; }
	else if (val == sf::Keyboard::BackSpace) { return true; }
	else if (val == sf::Keyboard::Up) { return true; }
	else if (val == sf::Keyboard::Down) { return true; }
	else if (val == sf::Keyboard::Left) { return true; }
	else if (val == sf::Keyboard::Right) { return true; }
	else if (val == sf::Keyboard::Delete) { return true; }
	else if (val == sf::Keyboard::Home) { return true; }
	else if (val == sf::Keyboard::End) { return true; }
	else if (val == sf::Keyboard::PageUp) { return true; }
	else if (val == sf::Keyboard::PageDown) { return true; }

	return false;
}