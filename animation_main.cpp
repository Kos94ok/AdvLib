
#include "stdafx.h"
#include "animation.h"
#include "texture.h"
#include "vectox.h"
#include "event.h"

void adv::cAnimatedDrawable::moveAnim(int time)
{
	__frameTime += time;
	if (__frameTime >= __animData[__animation].timePerFrame)
	{
		// Change the frame
		setFrame();
		// Reset the time
		__frameTime -= __animData[__animation].timePerFrame;
	}
}

void adv::cAnimatedDrawable::setFrame(int frame)
{
	this->_begin();
	// Next frame
	if (frame == -1) {
		__frame += 1;
		if (__frame >= (int)__animData[__animation].frameList.size())
		{
			if (__animData[__animation].nextAnimation != -1)
			{
				this->_end();
				setAnimation(__animData[__animation].nextAnimation);
				return;
			}
			else
				__frame = 0;
		}
	}
	// Random frame
	else {
		__frame = frame % (int)__animData[__animation].frameList.size();
	}
	texturize(__animData[__animation].frameList[__frame]);
	this->_end();
	advEvent.add(EVENT_ANIM_FRAME, cEventArgs(__animData[__animation].frameList[__frame], id(), getFlags()));
}

void adv::cAnimatedDrawable::setAnimation(int anim, bool reset)
{
	advEvent.add(EVENT_ANIM_END, cEventArgs(__animation, id(), getFlags()));
	this->_begin();
	__animation = anim;

	if (__frame >= (int)__animData[anim].frameList.size()) { reset = true; }

	if (reset) {
		__frame = 0;
		__frameTime = 0;
	}
	this->_end();
	setFrame(__frame);
	advEvent.add(EVENT_ANIM_BEGIN, cEventArgs(anim, id(), getFlags()));
}

void adv::cAnimatedDrawable::addFrame(int anim, int texture)
{
	this->_begin();
	__animData[anim].frameList.push_back(texture);
	// Check current animation
	if (anim == __animation && __frame == (int)__animData[anim].frameList.size() - 1)
	{
		texturize(__animData[__animation].frameList[__frame]);
	}
	this->_end();
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

void adv::cAnimatedDrawable::addAnimationTime(int anim, int time)
{
	this->_begin();
	__animData[anim].timePerFrame = time;
	this->_end();
}

void adv::cAnimatedDrawable::addAnimationChain(int anim, int nextAnim)
{
	this->_begin();
	__animData[anim].nextAnimation = nextAnim;
	this->_end();
}

void adv::cAnimatedDrawable::dropAnimation(int anim)
{
	this->_begin();
	__animData[anim].frameList.clear();
	__animData[anim].nextAnimation = -1;
	__animData[anim].timePerFrame = 1000;
	this->_end();
}