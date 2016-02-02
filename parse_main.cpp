
#include "stdafx.h"
#include "parse.h"

bool adv::cParse::toBool(int input)
{
	if (input <= 0) { return false; }
	return false;
}

int adv::cParse::toInt(bool input)
{
	if (input) { return 1; }
	return 0;
}

int adv::cParse::toInt(string input)
{
	int retVal;
	auto stream = stringstream(input);
	stream >> retVal;
	return retVal;
}

vector<int> adv::cParse::toIntVector(string input)
{
	vector<int> retVal;
	int val;
	auto stream = stringstream(input);
	while (stream >> val)
	{
		retVal.push_back(val);
	}
	return retVal;
}

float adv::cParse::toFloat(string input)
{
	float retVal;
	auto stream = stringstream(input);
	stream >> retVal;
	return retVal;
}

vector<float> adv::cParse::toFloatVector(string input)
{
	vector<float> retVal;
	float val;
	auto stream = stringstream(input);
	while (stream >> val)
	{
		retVal.push_back(val);
	}
	return retVal;
}

adv::cParse parse;