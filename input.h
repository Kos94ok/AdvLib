
#pragma once

#include "core.h"
#include "ui.h"

// Basic
#define INPUT_LATIN				1
#define INPUT_CYRILLIC			2
#define INPUT_SPACE				4
#define INPUT_NUMBERS			8
#define INPUT_SPECIAL			16

// Combined
#define INPUT_LETTERS			7
#define INPUT_NORMAL			15
#define INPUT_ANY				31

namespace adv
{
	class cInputMain
	{
	private:
		bool enabled = false;
		string id;

		wstring mainBuf;
		int validCharset;

		bool isCharValid(int val);
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
		// Get the input buffer string.
		*/
		wstring getString();
		/*
		// Enable input.
		*/
		void open(string id = "generic", int charset = INPUT_NORMAL);
		/*
		// Disable input. Buffer can be cleared or left as it is.
		*/
		void close(bool clearBuffer = true);
		/*
		// Clear input string.
		*/
		void clear();

		bool __isOpen() { return enabled; }
	};
}

extern adv::cInputMain advInput;