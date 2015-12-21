
#pragma once

#include "core.h"
#include "ui.h"

#define LIMIT_INPUTLINES		32

// Basic
#define INPUT_LATIN				1
#define INPUT_CYRILLIC			2
#define INPUT_SPACE				4
#define INPUT_NUMBERS			8
#define INPUT_SPECIAL			16

// Combined
#define INPUT_TEXT				7
#define INPUT_NORMAL			15
#define INPUT_ANY				31

namespace adv
{
	class cInputMain
	{
	private:
		bool _enabled = false;
		string _id;
		int _lineCount;
		int _lineMax;

		int _prefX;
		vec2i _caret;
		wstring _mainBuf[LIMIT_INPUTLINES];
		int _validCharset;

		sf::Mutex _mutex;

		bool __isCharValid(int val);
		bool __isCharSpecial(int val);
	public:
		/*
		// Add a character to the main string. Returns TRUE if the value is valid and FALSE if it's invalid.
		*/
		bool add(int character);
		/*
		// Add a string to the end of current string.
		*/
		void add(wstring str);
		/*
		// Handle a special key press.
		*/
		bool addSpec(int key);
		/*
		// Get the input buffer string. For multiline inputs, get one of the strings.
		*/
		wstring getString(int index = 0);
		/*
		// Get active input ID.
		*/
		string getId() { return _id; }
		/*
		// Get local caret position.
		*/
		vec2i getCaret() { return _caret; }
		/*
		// Get global caret position.
		*/
		vec2f getCaretPos(string fontId, int spacing = 0, wstring prefix = L"");
		/*
		// Enable input.
		*/
		void open(string id = "generic", int charset = INPUT_NORMAL, int lines = 1, bool clearBuffer = true);
		/*
		// Disable input. Buffer can be cleared or left as it is.
		*/
		void close(bool clearBuffer = true);
		/*
		// Clear input string.
		*/
		void clear();
		/*
		// Is the input currently enabled?
		*/
		bool isEnabled() { return _enabled; }
	};
}

extern adv::cInputMain advInput;