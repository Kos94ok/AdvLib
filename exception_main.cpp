
#include "stdafx.h"
#include "exception.h"

using namespace std;

void adv::cExceptionMain::crash(int code, string value)
{
	wstring msg;
	wstring wval = wstring(value.begin(), value.end());
	if (wval == L"-1") {
		wval = L"MISSINGNO";
	}

	if (code == CRASH_MISSINGNO) { msg = L"Incorrect index value: " + wval; }
	else if (code == CRASH_BADFONTID) { msg = L"Incorrect font ID: " + wval; }
	else if (code == CRASH_NOWINDOWFOUND) { msg = L"Incorrect UI window ID: " + wval; }
	else if (code == CRASH_NOELEMENTFOUND) { msg = L"Incorrect UI element ID: " + wval; }
	else if (code == CRASH_EXTERNAL) { msg = L"External error: " + wval; }

	else if (code == ERROR_DUPLISTENER) { msg = L"Duplicate event listener: " + wval; }
	else if (code == ERROR_INCORRECTUIMASK) { msg = L"Incorrect UI data mask: " + wval; }

#ifdef MODE_DEBUG
	MessageBox(0, msg.c_str(), L"Exception", MB_ICONSTOP);
#endif
}