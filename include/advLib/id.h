
#include "core.h"

namespace adv
{
	class cIDInternal
	{
	public:
		long __uniqueID;
		static long __nextID;
		long get() { return __uniqueID; }

		void increment()
		{
			__uniqueID = __nextID;
			__nextID += 1;
		}
		cIDInternal()
		{
			increment();
		}
		/*cIDInternal(const cIDInternal &obj)
		{
			increment();
		}*/
	};

	class cID
	{
	private:
		cIDInternal __idHandle;
	public:
		// Returns a unique object identifier.
		long id() { return __idHandle.get(); }
		// Creates a new unique object identifier.
		void makeUnique() { __idHandle.increment(); }

		bool operator==(int check)
		{
			if (id() == check) { return true; }
			return false;
		}
		bool operator==(long check)
		{
			if (id() == check) { return true; }
			return false;
		}
		bool operator==(cID check)
		{
			if (id() == check.id()) { return true; }
			return false;
		}
		bool operator==(cID* check)
		{
			if (id() == check->id()) { return true; }
			return false;
		}
		bool operator!=(int check) { return !operator==(check); }
		bool operator!=(long check) { return !operator==(check); }
		bool operator!=(cID check) { return !operator==(check); }
		bool operator!=(cID* check) { return !operator==(check); }
	};
}