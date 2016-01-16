
template<typename tObject> int adv::cDatabase<tObject>::addObject(string type, tObject entry)
{
	int sizeA, sizeB;
	__entryType.push_back(type);
	__entryList.push_back(entry);
	sizeA = __entryType.size();
	sizeB = __entryList.size();
	if (sizeA != sizeB) { advException.warning(WARNING::DBDESYNC, to_string(sizeA) + " | " + to_string(sizeB)); }

	return max(sizeA, sizeB);
}

template<typename tObject> tObject adv::cDatabase<tObject>::getCopy(string type)
{
	for (int i = 0; i < (int)min(__entryList.size(), __entryType.size()); i++)
	{
		if (__entryType[i] == type) { return __entryList[i]; }
	}
	advException.warning(WARNING::BADQUERY, type);
	return __entryList[0];
}

template<typename tObject> tObject* adv::cDatabase<tObject>::getHandle(string type)
{
	for (int i = 0; i < (int)min(__entryList.size(), __entryType.size()); i++)
	{
		if (__entryType[i] == type) { return __entryList[i]; }
	}
	advException.warning(WARNING::BADQUERY, type);
	return __entryList[0];
}