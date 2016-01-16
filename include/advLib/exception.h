
#include "stdafx.h"

namespace adv
{
	enum CRASH
	{
		BADINDEX,
		BADFONTID,
		BADUIWINDOWID,
		BADUIELEMENTID,
		EXTERNAL,
	};

	enum WARNING
	{
		BADQUERY,
		DUPLISTENER,
		DUPTIMER,
		BADUIMASK,
		DBDESYNC,
	};

	class cExceptionMain
	{
	public:
		void crash(int code, std::string value = "MISSINGNO");
		void warning(int code, std::string value = "MISSINGNO");
	};
}

extern adv::cExceptionMain advException;