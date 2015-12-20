
#include "core.h"

namespace adv
{
	template<class t> class vectox : public std::vector<t>
	{
	public:
		sf::Mutex access;
		void add(t obj)
		{
			access.lock();
			push_back(obj);
			access.unlock();
		}

		void remove(int index)
		{
			if (index > (int)size()) { return; }

			access.lock();
			t* info = data();
			info[index] = info[(int)size() - 1];
			pop_back();
			access.unlock();
		}
	};
}