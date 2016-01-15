
#include "stdafx.h"

class animatedObject : public adv::cAnimatedDrawable
{
public:
	float frameDelay = 0;
};

adv::cDatabase<animatedObject> testDB;
sf::Mutex mainvecLock;
vector<animatedObject> mainvec;

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

		texHandle.clear(color(100, 100, 100));
		advUI.paint(&texHandle);
		mainvecLock.lock();
		for (int i = 0; i < (int)mainvec.size(); i++)
		{
			mainvec[i].paint(&texHandle);
		}
		mainvecLock.unlock();
		texHandle.display();

		sf::Sprite spr;
		spr.setTexture(texHandle.getTexture());
		winHandle.draw(spr);
		winHandle.display();
	}
	advCore.stopThread(id);
}

void timerTick(adv::cEventArgs args)
{
	mainvecLock.lock();
	for (int i = 0; i < mainvec.size(); i++)
	{
		mainvec[i].frameDelay += args.timer_tickDelay;
		if (mainvec[i].frameDelay >= 1.50f) {
			mainvec[i].setFrame();
			mainvec[i].frameDelay = 0.00f;
		}
	}
	mainvecLock.unlock();

	advTimer.start(0.10f, "timer_test");
}

int main()
{
	advCore.init();
	advTimer.start(1.50f, "timer_test");
	advEvent.listen(EVENT_TIMER_END, timerTick, "timer_test");

	advUI.addFont("fontConsole", "C:/Windows/Fonts/consola.ttf", 16);
	adv::cUIWindow* wnd = advUI.addWindow("wndMain");
	wnd->addLabel("label0", vec2f(0, 0), L"Test String", "fontConsole", color(255, 255, 255));

	animatedObject obj;
	obj.moveto(vec2f(10, 10));
	obj.resize(vec2f(24, 24));
	obj.addFrame(adv::ANIM::IDLE, "ui_icon_close_white.png");
	obj.addFrame(adv::ANIM::IDLE, "ui_icon_close_orange.png");
	obj.setAnimation(adv::ANIM::IDLE);
	testDB.addObject("test", obj);

	obj = testDB.getCopy("test");
	obj.move(vec2f(10, 10));
	mainvec.push_back(obj);
	obj = testDB.getCopy("test");
	obj.move(vec2f(30, 10));
	mainvec.push_back(obj);
	obj = testDB.getCopy("tests");
	obj.move(vec2f(50, 10));
	mainvec.push_back(obj);

	advCore.addThread(threadWindow, 0);

	advCore.mainLoop();
	advCore.shut();

	return 0;
}

