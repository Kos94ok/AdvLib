
#include "stdafx.h"
#include "ui.h"

using namespace std;
using namespace adv;

void adv::threadUIMain(int id, cArgs args)
{
	int oldTime = timeGetTime();
	while (advCore.isThreadGood(id))
	{
		int newTime = timeGetTime();
		int elapsedTime = newTime - oldTime;
		float timevar = (float)elapsedTime / 1000.00f;
		oldTime = newTime;

		// For each fadeout UI button
		for (int i = 0; i < (int)advUI.__fadeoutUIButtons.size(); i++)
		{
			// Check if the button is hovered again
			if (find(advUI.__hoveredUIButtons.begin(), advUI.__hoveredUIButtons.end(), advUI.__fadeoutUIButtons[i]) != advUI.__hoveredUIButtons.end())
			{
				advUI.__fadeoutUIButtons.erase(advUI.__fadeoutUIButtons.begin() + i, advUI.__fadeoutUIButtons.begin() + i + 1);
				i -= 1;
			}
			else
			{
				// Reduce the time
				advUI.__fadeoutUIButtons[i]->_setButtonFadeCur(advUI.__fadeoutUIButtons[i]->_getButtonFadeCur() - timevar);
				// If the time is zero, the button is no longer fadeout
				if (advUI.__fadeoutUIButtons[i]->_getButtonFadeCur() <= 0.00f)
				{
					advUI.__fadeoutUIButtons[i]->_setButtonFadeCur(0.00f);
					advUI.__fadeoutUIButtons.erase(advUI.__fadeoutUIButtons.begin() + i, advUI.__fadeoutUIButtons.begin() + i + 1);
					i -= 1;
				}
			}
		}
		Sleep(5);
	}
	advCore.stopThread(id);
}