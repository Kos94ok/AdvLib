
#include "stdafx.h"
#include "animation.h"
#include "texture.h"

void adv::cAnimatedDrawable::setFrame(int frame)
{
	// Next frame
	if (frame == -1) {
		__frame += 1;
		if (__frame >= (int)__animData[__animation].frameList.size()) {
			__frame = 0;
		}
	}
	// Random frame
	else {
		__frame = frame % (int)__animData[__animation].frameList.size();
	}
	texturize(__animData[__animation].frameList[__frame]);
}

void adv::cAnimatedDrawable::setAnimation(int anim, bool reset)
{
	__animation = anim;

	if (__frame >= (int)__animData[anim].frameList.size()) { reset = true; }

	if (reset) {
		__frame = 0;
	}
	setFrame(__frame);
}

#include "vectox.h"
void adv::cAnimatedDrawable::addFrame(int anim, int texture)
{
	//vectox<int>(1, 2, 3);
	vector<int> test;
	__animData[anim].frameList.push_back(texture);
	// Check current animation
	if (anim == __animation)
	{

	}
}

void adv::cAnimatedDrawable::addFrame(int anim, string texture)
{
	return addFrame(anim, advTexture.add(texture));
}

void adv::cAnimatedDrawable::addAnimation(int anim, vector<int> textureList)
{
	for (int i = 0; i < (int)textureList.size(); i++) {
		addFrame(anim, textureList[i]);
	}
}

void adv::cAnimatedDrawable::addAnimation(int anim, vector<string> textureList)
{
	for (int i = 0; i < (int)textureList.size(); i++) {
		addFrame(anim, textureList[i]);
	}
}

void adv::cAnimatedDrawable::dropAnimation(int anim)
{
	__animData[anim].frameList.clear();
}