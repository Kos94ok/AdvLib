
#include "stdafx.h"
#include "game.h"
#include "window.h"
#include "camera.h"
#include "database.h"
#include "flag.h"

//====================================================================================
// Source code
//====================================================================================
cScene testScene;

void threadWindow(int id, adv::cArgs args)
{
	sf::RenderWindow winHandle(sf::VideoMode((int)Camera.MainSize.x, (int)Camera.MainSize.y), "Taiga 5.1", 7U);
	winHandle.setKeyRepeatEnabled(false);
	//winHandle.setVerticalSyncEnabled(true);
	sf::RenderTexture texHandle;
	texHandle.create((int)Camera.MainSize.x, (int)Camera.MainSize.y);

	sf::Transform mainMatrix;
	while (advCore.isThreadGood(id))
	{
		sf::Event eventPoll;
		while (winHandle.pollEvent(eventPoll)) {
			advEvent.handle(eventPoll, &winHandle);
		}
		mainMatrix = sf::Transform::Identity;
		mainMatrix.translate(Camera.MainOffset);
		//Camera.Lock();
		mainMatrix.translate(-Camera.Position);
		//Camera.Unlock();
		texHandle.clear(color(100, 100, 100));

		Game.TestScene.paint(&texHandle, mainMatrix);
		Game.Hero.paint(&texHandle, mainMatrix);
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
	hdb.centralize(vec2f(16, 16));
	hdb.addAnimationTime(adv::ANIM::IDLE, 150);
	hdb.addFrame(adv::ANIM::IDLE, "hero_idle00.png");
	hdb.addFrame(adv::ANIM::IDLE, "hero_idle01.png");
	hdb.addFrame(adv::ANIM::IDLE, "hero_idle02.png");
	hdb.addFrame(adv::ANIM::IDLE, "hero_idle03.png");
	hdb.AddHover(3.00f, 0.5f);

	cUnit db;
	db = cUnit();
	db.resize(vec2f(128, 8));
	db.centralize(vec2f(64, 4));
	db.addFrame(adv::ANIM::IDLE, "black.png");
	Database.Unit.addObject("land", db);

	cEnemy edb;
	edb.AttackType = cEnemy::AttackType::SnakeShooting;
	edb.resize(vec2f(48, 48));
	edb.centralize(vec2f(24, 24));
	edb.addAnimationTime(adv::ANIM::IDLE, 500);
	edb.addFrame(adv::ANIM::IDLE, "snake_idle00.png");
	edb.addFrame(adv::ANIM::IDLE, "snake_idle01.png");
	edb.addAnimationTime(adv::ANIM::ATTACK, 250);
	edb.addAnimationTime(adv::ANIM::ATTACK_END, 250);
	edb.addFrame(adv::ANIM::ATTACK, "snake_attack00.png");
	edb.addFrame(adv::ANIM::ATTACK, "snake_attack01.png");
	edb.addFrame(adv::ANIM::ATTACK_END, "snake_attack02.png");
	edb.addFrame(adv::ANIM::ATTACK_END, "snake_idle00.png");
	edb.addFrame(adv::ANIM::ATTACK_END, "snake_idle01.png");
	edb.addAnimationChain(adv::ANIM::ATTACK, adv::ANIM::ATTACK_END);
	edb.addAnimationChain(adv::ANIM::ATTACK_END, adv::ANIM::IDLE);
	edb.Plane = cPlane::Background;
	edb.addFlag(cFlag::EnemySnake);
	Database.Enemy.addObject("snake", edb);

	edb.makeUnique();
	edb.dropAnimation(adv::ANIM::ATTACK);
	edb.dropAnimation(adv::ANIM::ATTACK_END);
	edb.addAnimationTime(adv::ANIM::ATTACK, 250);
	edb.addAnimationTime(adv::ANIM::ATTACK_END, 250);
	edb.addFrame(adv::ANIM::ATTACK, "snake_attack00.png");
	edb.addFrame(adv::ANIM::ATTACK, "snake_attack01.png");
	edb.addFrame(adv::ANIM::ATTACK, "snake_attack02.png");
	edb.addFrame(adv::ANIM::ATTACK, "snake_attack01.png");
	edb.addFrame(adv::ANIM::ATTACK, "snake_attack02.png");
	edb.addFrame(adv::ANIM::ATTACK, "snake_attack01.png");
	edb.addFrame(adv::ANIM::ATTACK_END, "snake_attack02.png");
	edb.addFrame(adv::ANIM::ATTACK_END, "snake_idle00.png");
	edb.addFrame(adv::ANIM::ATTACK_END, "snake_idle01.png");
	edb.addAnimationChain(adv::ANIM::ATTACK, adv::ANIM::ATTACK_END);
	edb.addAnimationChain(adv::ANIM::ATTACK_END, adv::ANIM::IDLE);
	Database.Enemy.addObject("snake_imba", edb);

	cMissile mdb;
	mdb.resize(vec2f(16, 16));
	mdb.centralize(vec2f(8, 8));
	mdb.addFrame(adv::ANIM::IDLE, "snake_missile.png");
	mdb.Plane = cPlane::Background;
	mdb.AddRotation(360);
	mdb.AddLifeTimer(1.50f);
	Database.Missile.addObject("snake", mdb);
	mdb = cMissile();
	mdb.resize(vec2f(20, 10));
	mdb.centralize(vec2f(10, 5));
	mdb.addAnimationTime(adv::ANIM::IDLE, 100);
	mdb.addFrame(adv::ANIM::IDLE, "hero_soulshard_missile00.png");
	mdb.addFrame(adv::ANIM::IDLE, "hero_soulshard_missile01.png");
	mdb.addFrame(adv::ANIM::IDLE, "hero_soulshard_missile02.png");
	mdb.addFrame(adv::ANIM::IDLE, "hero_soulshard_missile03.png");
	mdb.Plane = cPlane::Background;
	mdb.AddLifeTimer(2.50f);
	Database.Missile.addObject("hero_soulshard", mdb);

	// Creating test scene
	hdb.moveto(vec2f(0, 0));
	hdb.HomeScene = &Game.TestScene;
	Game.Hero = hdb;
	edb = Database.Enemy.getCopy("snake");
	edb.moveto(vec2f(400, 0));
	Game.AddEnemy(edb, &Game.TestScene);
	edb.makeUnique();
	edb.moveto(vec2f(-100, 0));
	Game.AddEnemy(edb, &Game.TestScene);
	edb = Database.Enemy.getCopy("snake_imba");
	edb.moveto(vec2f(800, 0));
	Game.AddEnemy(edb, &Game.TestScene);

	db = Database.Unit.getCopy("land");
	db.moveto(vec2f(400, 300));
	Game.AddUnit(db, &Game.TestScene);
	db.makeUnique();
	db.moveto(vec2f(-100, 300));
	Game.AddUnit(db, &Game.TestScene);
	db.makeUnique();
	db.moveto(vec2f(0, 550));
	Game.AddUnit(db, &Game.TestScene);
	db.makeUnique();
	db.moveto(vec2f(100, 400));
	Game.AddUnit(db, &Game.TestScene);
	db.makeUnique();
	db.moveto(vec2f(600, 250));
	Game.AddUnit(db, &Game.TestScene);
	db.makeUnique();
	db.moveto(vec2f(800, 100));
	Game.AddUnit(db, &Game.TestScene);
	db.makeUnique();
	db.moveto(vec2f(100, 500));
	Game.AddUnit(db, &Game.TestScene);
	db.makeUnique();
	db.moveto(vec2f(150, 550));
	Game.AddUnit(db, &Game.TestScene);

	// Creating logic timers
	advEvent.listenForTimer(TIMER_100MS, cGame::TimerAnimation);
	advEvent.listenForTimer(TIMER_10MS, cGame::TimerHeroMovement);
	advEvent.listenForTimer(TIMER_10MS, cGame::TimerEnemyMovement);
	advEvent.listenForTimer(TIMER_10MS, cGame::TimerMissileMovement);
	advEvent.listenForTimer(TIMER_50MS, cGame::TimerEnemyAI);
	advEvent.listenForTimer(TIMER_10MS, cCamera::TimerAcceleration);
	advEvent.listenForTimer(TIMER_100MS, bind(&cHero::TimerShooting, &Game.Hero, _1));
	advEvent.listen(EVENT_KEY_PRESS, bind(&cHero::Jump, &Game.Hero, _1), sf::Keyboard::W);
	advEvent.listen(EVENT_KEY_PRESS, bind(&cHero::Respawn, &Game.Hero, _1), sf::Keyboard::R);
	advEvent.listen(EVENT_MOUSE_PRESS, bind(&cHero::Shoot, &Game.Hero, _1), sf::Mouse::Left);
	advEvent.listen(EVENT_MOUSE_MOVE, cCamera::EventMouseMove);
	//advEvent.listen(EVENT_ANIM_BEGIN, cGame::EnemySnakeMissile, adv::ANIM::ATTACK_END, cFlag::EnemySnake);
	advEvent.listen(EVENT_ANIM_FRAME, cGame::EnemySnakeMissile, advTexture.add("snake_attack02.png"), cFlag::EnemySnake);
	
	advCore.addThread(threadWindow, 0);

	advCore.mainLoop();
	advCore.shut();

	return 0;
}

