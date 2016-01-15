
#include "core.h"

namespace adv
{
	template<typename tObject> class cDatabase
	{
	private:
		sf::Mutex __access;

		vector<string> __entryType;
		vector<tObject> __entryList;
	public:
		void lock() { __access.lock(); }
		void unlock() { __access.unlock(); }
		/*
		// Add a new object to the database.
		*/
		int addObject(string type, tObject entry);
		/*
		// Get a copy of an object with the given type. If the object is not found, exception is shot and MISSINGNO is returned.
		*/
		tObject getCopy(string type);
		/*
		// Get a handle of an object with the given type. If the object is not found, exception is shot and MISSINGNO is returned.
		*/
		tObject* getHandle(string type);
		/*
		// Check if there is an object with the given type in the database.
		*/
		bool isQueryValid(string type);

		/*
		// Default constructor will always add a missingno to the beginning of the list.
		*/
		cDatabase() {
			tObject missingno;
			addObject("MISSINGNO", missingno);
		}
	};
}