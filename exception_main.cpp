
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

	if (code == CRASH::BADINDEX) { msg = L"Incorrect index value: " + wval; }
	else if (code == CRASH::BADFONTID) { msg = L"Incorrect font ID: " + wval; }
	else if (code == CRASH::BADUIWINDOWID) { msg = L"Incorrect UI window ID: " + wval; }
	else if (code == CRASH::BADUIELEMENTID) { msg = L"Incorrect UI element ID: " + wval; }
	else if (code == CRASH::EXTERNAL) { msg = L"External error: " + wval; }

	MessageBox(0, msg.c_str(), L"Exception", MB_ICONSTOP);
}

void adv::cExceptionMain::warning(int code, string value)
{
	wstring msg;
	wstring wval = wstring(value.begin(), value.end());
	if (wval == L"-1") {
		wval = L"MISSINGNO";
	}

	if (code == WARNING::BADUIMASK) { msg = L"Incorrect UI data mask: " + wval; }
	else if (code == WARNING::BADQUERY) { msg = L"Incorrect database query: " + wval; }
	else if (code == WARNING::DUPLISTENER) { msg = L"Duplicate event listener: " + wval; }
	else if (code == WARNING::DBDESYNC) { msg = L"Database desync: " + wval; }

#ifdef MODE_DEBUG
	MessageBox(0, msg.c_str(), L"Warning", MB_ICONWARNING);
#endif
}