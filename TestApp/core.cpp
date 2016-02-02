
#include "stdafx.h"
#include "game.h"
#include "window.h"

//====================================================================================
// Source code
//====================================================================================
cScene testScene;
adv::cDatabase<cUnit> unitDB;

void threadWindow(int id, adv::cArgs args)
{
	sf::RenderWindow winHandle(sf::VideoMode(800, 600), "Window", 7U);
	winHandle.setKeyRepeatEnabled(false);
	sf::RenderTexture texHandle;
	texHandle.create(800, 600);

	while (advCore.isThreadGood(id)) {
		sf::Event eventPoll;
		while (winHandle.pollEvent(eventPoll)) {
			advEvent.handle(eventPoll, &winHandle);
		}

		texHandle.clear(color(100, 100, 100));
		//testScene.paint(&texHandle);
		Game.TestScene.paint(&texHandle);
		Game.Hero.paint(&texHandle);
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
	//adv::cUIWindow* wnd = advUI.addWindow("wndMain");
	//wnd->addLabel("label0", vec2f(0, 0), L"Test String", "fontConsole", color(255, 255, 255));

	// Pushing object to the database
	cHero hdb;
	hdb.resize(vec2f(32, 32));
	//hdb.centralize(vec2f(16, 16));
	hdb.addFrame(adv::ANIM::IDLE, "charglow_idle00.png");
	hdb.addFrame(adv::ANIM::IDLE, "charglow_idle01.png");
	hdb.addFrame(adv::ANIM::IDLE, "charglow_idle02.png");
	hdb.addFrame(adv::ANIM::IDLE, "charglow_idle03.png");
	//hdb.setAnimation(adv::ANIM::IDLE);

	cUnit db;
	db = cUnit();
	db.resize(vec2f(128, 8));
	//db.centralize(vec2f(64, 4));
	db.addFrame(adv::ANIM::IDLE, "black.png");
	//db.setAnimation(adv::ANIM::IDLE);
	unitDB.addObject("land", db);

	// Creating test scene
	hdb.moveto(vec2f(0, 0));
	Game.Hero = hdb;
	for (int i = 0; i < 10; i++)
	{
		db = unitDB.getCopy("land");
		db.moveto(vec2f(advMath.randf(0.0f, 800.0f), advMath.randf(0.00f, 600.0f)));
		Game.TestScene.UnitList.push_back(db);
	}
	db = unitDB.getCopy("land");
	db.moveto(vec2f(0, 550));
	Game.TestScene.UnitList.push_back(db);

	// Creating logic timers
	advEvent.listenForTimer(TIMER_10MS, cGame::TimerHeroMovement);
	advEvent.listen(EVENT_KEY_PRESS, bind(&cHero::Jump, &Game.Hero, _1), sf::Keyboard::W);
	advEvent.listen(EVENT_KEY_PRESS, bind(&cHero::Respawn, &Game.Hero, _1), sf::Keyboard::R);
	
	advCore.addThread(threadWindow, 0);

	advCore.mainLoop();
	advCore.shut();

	return 0;
}

