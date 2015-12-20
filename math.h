
#include "stdafx.h"

using namespace std;

namespace adv
{
	class cMath
	{
	public:
		int round(float num);
		vec2f round(vec2f num);
		float getDistance(float ax, float ay, float bx, float by);
		float getDistance(vec2f &a, vec2f &b);
		float getDistance(vec2i &a, vec2i &b);
		float getAngle(float ax, float ay, float bx, float by);
		float getAngle(vec2f a, vec2f b);
		float getAngle(vec2i a, vec2i b);
		float polarX(float x, float dist, float angle);
		float polarY(float y, float dist, float angle);
		vec2f polar(vec2f point, float dist, float angle);
		float randf(float min, float max);
		float srandf(float val);
		int rand(int min, int max);
		int srand(int val);
		float randAngle();
		float convertAngle(float angle);
		bool intToBool(int a);
		bool stringToBool(string str);
		int boolToInt(bool a);
		int stringToInt(string str);
		bool isPointInRect(float x, float y, float rectX, float rectY, float rectSizeX, float rectSizeY);

		float PI = 3.14159f;
		float RADTODEG = 180.00f / PI;
		float DEGTORAD = PI / 180.00f;
	};
}

extern adv::cMath math;