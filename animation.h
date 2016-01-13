
#include "core.h"
#include "drawable.h"

namespace adv
{
	class cAnimatedDrawable : public cDrawable
	{
	private:
		int __frame;
		vector<int> __frameList;
	public:
		int frame() { return __frame; }		// Get current frame
		
		void animate(int frame = -1);		// Set the animation frame. If 'frame' == -1, set the next frame

		/*
		// Create the frame list.
		*/
		void addFrame(int frame);
		void addFrame(string frame);
		void addAnimation(vector<int> frameList);
		void addAnimation(vector<string> frameList);
	};
}