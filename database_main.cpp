
#include "stdafx.h"
#include "database.h"

template<typename tObject> bool adv::cDatabase<tObject>::isQueryValid(string type)
{
	for (int i = 0; i < (int)__entryType.size(); i++)
	{
		if (__entryType[i] == type) { return true; }
	}
	return false;
}