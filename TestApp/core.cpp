
#include "stdafx.h"

class animatedObject : public adv::cAnimatedDrawable
{

};

void threadWindow(int id, adv::cArgs args)
{
	sf::RenderWindow winHandle(sf::VideoMode(800, 600), "Window", 7U);
	sf::RenderTexture texHandle;
	texHandle.create(800, 600);

	while (advCore.isThreadGood(id)) {
		sf::Event eventPoll;
		while (winHandle.pollEvent(eventPoll)) {
			advEvent.handle(eventPoll, &winHandle);
		}

		texHandle.clear();
		advUI.paint(&texHandle);
		texHandle.display();

		sf::Sprite spr;
		spr.setTexture(texHandle.getTexture());
		winHandle.draw(spr);
		winHandle.display();
	}
	advCore.stopThread(id);
}

int main()
{
	advCore.init();

	advUI.addFont("fontConsole", "C:/Windows/Fonts/consola.ttf", 16);
	adv::cUIWindow* wnd = advUI.addWindow("wndMain");
	wnd->addLabel("label0", vec2f(0, 0), L"Test String", "fontConsole", color(255, 255, 255));

	//animatedObject obj;

	advCore.addThread(threadWindow, 0);

	advCore.mainLoop();
	advCore.shut();

	return 0;
}

