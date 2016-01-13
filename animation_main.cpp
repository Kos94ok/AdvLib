
#include "header.h"
#include "animation.h"
#include "texture.h"

void adv::cAnimatedDrawable::animate(int frame)
{
	// Next frame
	if (frame == -1) {
		__frame += 1;
		if (__frame >= (int)__frameList.size()) {
			__frame = 0;
		}
	}
	// Random frame
	else {
		__frame = frame % (int)__frameList.size();
	}
	texturize(__frame);
}

void adv::cAnimatedDrawable::addFrame(int frame)
{

}

void adv::cAnimatedDrawable::addFrame(string frame)
{
	return addFrame(advTexture.add(frame));
}

void adv::cAnimatedDrawable::addAnimation(vector<int> frameList)
{
	for (int i = 0; i < (int)frameList.size(); i++) {
		addFrame(frameList[i]);
	}
}

void adv::cAnimatedDrawable::addAnimation(vector<string> frameList)
{
	for (int i = 0; i < (int)frameList.size(); i++) {
		addFrame(frameList[i]);
	}
}