
#include "stdafx.h"
#include "scene.h"

class cGame
{
public:
	cHero Hero;
	cScene TestScene;
	cScene* ActiveScene = &TestScene;

	void AddUnit(cUnit Data, cScene* HomeScene);
	void AddEnemy(cEnemy Data, cScene* HomeScene);
	void AddMissile(cMissile Data, cScene* HomeScene);
	void AddMissile(string ID, vec2f Origin, vec2f Target, float Speed, int Owner, cScene* HomeScene);

	static void EnemySnakeMissile(adv::cEventArgs args);
	static void TimerAnimation(adv::cEventArgs args);
	static void TimerHeroMovement(adv::cEventArgs args);
	static void TimerEnemyMovement(adv::cEventArgs args);
	static void TimerEnemyAI(adv::cEventArgs args);
	static void TimerMissileMovement(adv::cEventArgs args);
};

extern cGame Game;