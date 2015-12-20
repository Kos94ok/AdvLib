
#include "stdafx.h"
#include "math.h"

adv::cMath math;

int adv::cMath::round(float num) {
	return (int)(num < 0 ? num - 0.5 : num + 0.5);
}

vec2f adv::cMath::round(vec2f num) {
	return vec2f((float)round(num.x), (float)round(num.y));
}

float adv::cMath::getDistance(float ax, float ay, float bx, float by) {
	return sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
}

float adv::cMath::getDistance(vec2f &a, vec2f &b) {
	return getDistance(a.x, a.y, b.x, b.y);
}

float adv::cMath::getDistance(vec2i &a, vec2i &b) {
	return getDistance((float)a.x, (float)a.y, (float)b.x, (float)b.y);
}

float adv::cMath::getAngle(float ax, float ay, float bx, float by) {
	return math.RADTODEG * atan2(by - ay, bx - ax);
}

float adv::cMath::getAngle(vec2f a, vec2f b) {
	return getAngle(a.x, a.y, b.x, b.y);
}

float adv::cMath::getAngle(vec2i a, vec2i b) {
	return getAngle((float)a.x, (float)a.y, (float)b.x, (float)b.y);
}

float adv::cMath::polarX(float x, float dist, float angle) {
	return x + dist * cos(angle * math.DEGTORAD);
}

float adv::cMath::polarY(float y, float dist, float angle) {
	return y + dist * sin(angle * math.DEGTORAD);
}

vec2f adv::cMath::polar(vec2f point, float dist, float angle) {
	return vec2f(polarX(point.x, dist, angle), polarY(point.y, dist, angle));
}

float adv::cMath::randf(float min, float max) {
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<float> dist(min, max);

	return dist(mt);
}

float adv::cMath::srandf(float val) {
	return randf(-val, val);
}

int adv::cMath::rand(int min, int max) {
	return round(randf((float)min, (float)max));
}

int adv::cMath::srand(int val) {
	return rand(-val, val);
}

float adv::cMath::randAngle() {
	return randf(0.00f, 360.00f);
}

// Convert the angle from [-180; 180] to [0; 360]
float adv::cMath::convertAngle(float angle)
{
	if (angle < 0) { angle += 360; }
	angle = 360 - angle;
	return angle;
}

bool adv::cMath::intToBool(int a) {
	if (a <= 0) { return false; }
	return true;
}

bool adv::cMath::stringToBool(string str) {
	return intToBool(stringToInt(str));
}

int adv::cMath::boolToInt(bool a) {
	if (a) { return 1; }
	return 0;
}

int adv::cMath::stringToInt(string str) {
	int tmp;
	stringstream(str) >> tmp;
	return tmp;
}

bool adv::cMath::isPointInRect(float x, float y, float rectX, float rectY, float rectSizeX, float rectSizeY)
{
	if (x < rectX) { return false; }
	if (y < rectY) { return false; }
	if (x > rectX + rectSizeX) { return false; }
	if (y > rectY + rectSizeY) { return false; }
	return true;
}