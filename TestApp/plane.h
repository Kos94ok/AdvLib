
#pragma once

#include "stdafx.h"

class cPlane
{
public:
	enum
	{
		Foreground,
		Gameplay,
		Background,
	};
};

class cOwner
{
public:
	enum
	{
		Player,
		Enemy,
		Neutral,
	};
};

class cFacing
{
public:
	enum
	{
		Left,
		Right,
	};
};