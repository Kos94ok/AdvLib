
#include "core.h"

namespace adv
{
	class cParse
	{
		bool toBool(int input);
		int toInt(bool input);
		int toInt(string input);
		vector<int> toIntVector(string input);
		float toFloat(bool input);
		float toFloat(string input);
		vector<float> toFloatVector(string input);
	};
}

extern adv::cParse parse;