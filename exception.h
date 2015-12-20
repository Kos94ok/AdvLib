
#include "stdafx.h"

#define CRASH_MISSINGNO						1000
#define CRASH_BADFONTID						1001
#define CRASH_NOWINDOWFOUND					1003
#define CRASH_NOELEMENTFOUND				1004
#define CRASH_EXTERNAL						1005
#define ERROR_DUPLISTENER					1100
#define ERROR_INCORRECTUIMASK				1101

namespace adv
{
	class cExceptionMain
	{
	public:
		void crash(int code, std::string value = "MISSINGNO");
	};
}

extern adv::cExceptionMain advException;