
#include "core.h"

namespace adv
{
	template<class t> class vectox : public std::vector<t>
	{
	public:
		sf::Mutex access;
		void lock() { access.lock(); }
		void unlock() { access.unlock(); }
		int count()
		{
			int retVal;
			access.lock();
			retVal = (int)size();
			access.unlock();
			return retVal;
		}
		void push(t obj)
		{
			access.lock();
			push_back(obj);
			access.unlock();
		}
		void pop()
		{
			access.lock();
			pop_back();
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

		vectox() {}
		template<class t>vectox(t a0)
		{
			push(a0);
		}
		template<class t>vectox(t a0, t a1)
		{
			push(a0);	push(a1);
		}
		template<class t>vectox(t a0, t a1, t a2)
		{
			push(a0);	push(a1);	push(a2);
		}
		template<class t>vectox(t a0, t a1, t a2, t a3)
		{
			push(a0);	push(a1);	push(a2);	push(a3);
		}
		template<class t>vectox(t a0, t a1, t a2, t a3, t a4)
		{
			push(a0);	push(a1);	push(a2);	push(a3);	push(a4);
		}
		template<class t>vectox(t a0, t a1, t a2, t a3, t a4, t a5)
		{
			push(a0);	push(a1);	push(a2);	push(a3);	push(a4);	push(a5);
		}
	};
}