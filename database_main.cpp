
#include "stdafx.h"
#include "database.h"

template<typename tObject> int adv::cDatabase<tObject>::addObject(string type, tObject entry)
{
	__entryType.push_back(type);
	__entryList.push_back(entry);
}

template<typename tObject> tObject adv::cDatabase<tObject>::getCopy(string type)
{
	for (int i = 0; i < (int)min(__entryList.size(), __entryType.size()); i++)
	{
		if (__entryType[i] == type) { return __entryList[i]; }
	}
	return __entryList[0];
}

template<typename tObject> tObject* adv::cDatabase<tObject>::getHandle(string type)
{
	for (int i = 0; i < (int)min(__entryList.size(), __entryType.size()); i++)
	{
		if (__entryType[i] == type) { return __entryList[i]; }
	}
	return __entryList[0];
}

template<typename tObject> bool adv::cDatabase<tObject>::isQueryValid(string type)
{
	for (int i = 0; i < (int)__entryType.size(); i++)
	{
		if (__entryType[i] == type) { return true; }
	}
	return false;
}