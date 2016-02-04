
#include "stdafx.h"
#include "game.h"
#include "camera.h"
#include "database.h"

cGame Game;

void cGame::AddUnit(cUnit Data, cScene* HomeScene)
{
	Data.HomeScene = HomeScene;
	HomeScene->UnitList.push(Data);
}

void cGame::AddEnemy(cEnemy Data, cScene* HomeScene)
{
	Data.HomeScene = HomeScene;
	HomeScene->EnemyList.push(Data);
}

void cGame::AddMissile(cMissile Data, cScene* HomeScene)
{
	Data.HomeScene = HomeScene;
	HomeScene->MissileList.push(Data);
}

void cGame::AddMissile(string ID, vec2f Origin, vec2f Target, float Speed, int Owner, cScene* HomeScene)
{
	cMissile db = Database.Missile.getCopy(ID);
	db.moveto(Origin);
	float Angle = advMath.getAngle(Origin, Target);
	db.faceto(Angle);
	db.MovingVector = advMath.polar(Origin, Speed, Angle) - Origin;
	db.Owner = Owner;
	AddMissile(db, HomeScene);
}

void cGame::EnemySnakeMissile(adv::cEventArgs args)
{
	int id = args.sourceId;
	for (int i = 0; i < Game.ActiveScene->EnemyList.count(); i++)
	{
		cEnemy Enemy = Game.ActiveScene->EnemyList[i];
		if (Enemy == id)
		{
			Game.AddMissile("snake", Enemy.pos(), Game.Hero.pos(), Database.Snake_Missile_Speed, cOwner::Enemy, Game.ActiveScene);
			break;
		}
	}
}

void cGame::TimerAnimation(adv::cEventArgs args)
{
	float timemod = args.timer_tickDelay;

	Game.Hero.moveAnim((int)(timemod * 1000));
	for (int i = 0; i < (int)Game.ActiveScene->UnitList.size(); i++)
	{
		Game.ActiveScene->UnitList[i].moveAnim((int)(timemod * 1000));
	}
	for (int i = 0; i < (int)Game.ActiveScene->EnemyList.size(); i++)
	{
		Game.ActiveScene->EnemyList[i].moveAnim((int)(timemod * 1000));
	}
	for (int i = 0; i < (int)Game.ActiveScene->MissileList.size(); i++)
	{
		Game.ActiveScene->MissileList[i].moveAnim((int)(timemod * 1000));
		Game.ActiveScene->MissileList[i].rotate(Game.ActiveScene->MissileList[i].RotationSpeed * timemod);
	}
}

void cGame::TimerHeroMovement(adv::cEventArgs args)
{
	float timemod = args.timer_tickDelay;

	float speedX = 250.00f * timemod;
	float accY = 10.f * timemod;
	Camera.Lock();
	cHero* hero = &Game.Hero;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		hero->move(vec2f(-speedX, 0.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		hero->move(vec2f(speedX, 0.f));
	}

	if (hero->VertAccel >= 0.00f && hero->CheckFalling())
	{
		hero->move(vec2f(0.f, hero->VertAccel));
		hero->VertAccel += accY;
	}
	else if (hero->VertAccel < 0.00f && hero->CheckRising())
	{
		hero->move(vec2f(0.f, hero->VertAccel));
		hero->VertAccel += accY;
	}
	else
	{
		hero->VertAccel = 0.00f;
	}
	Camera.AnchorTo(vec2f(hero->pos().x, 0.00f));
	Camera.Unlock();

	hero->MoveHover((int)(timemod * 1000));
}

void cGame::TimerEnemyMovement(adv::cEventArgs args)
{
	float timemod = args.timer_tickDelay;
	float accY = 10.f * timemod;

	for (int i = 0; i < Game.ActiveScene->EnemyList.count(); i++)
	{
		cEnemy* Enemy = &Game.ActiveScene->EnemyList[i];
		if (Enemy->VertAccel >= 0.00f && Enemy->CheckFalling())
		{
			Enemy->move(vec2f(0.f, Enemy->VertAccel));
			Enemy->VertAccel += accY;
		}
	}
}

void cGame::TimerEnemyAI(adv::cEventArgs args)
{
	float timemod = args.timer_tickDelay;

	for (int i = 0; i < Game.ActiveScene->EnemyList.count(); i++)
	{
		cEnemy* Enemy = &Game.ActiveScene->EnemyList[i];
		// Attacking
		switch (Enemy->AttackType)
		{
		case cEnemy::AttackType::SnakeShooting:
			// Facing
			if (Game.Hero.pos().x < Enemy->pos().x)
				Enemy->SetFacing(cFacing::Left);
			else
				Enemy->SetFacing(cFacing::Right);
			// Attacking
			if (advMath.getDistance(Enemy->pos(), Game.Hero.pos()) <= 400
				&& Enemy->animation() == adv::ANIM::IDLE)
			{
				Enemy->setAnimation(adv::ANIM::ATTACK);
			}

			break;
		}
	}
}

void cGame::TimerMissileMovement(adv::cEventArgs args)
{
	float timemod = args.timer_tickDelay;
	float accY = 10.f * timemod;

	for (int i = 0; i < Game.ActiveScene->MissileList.count(); i++)
	{
		bool MissileRemoved = false;
		cMissile* Missile = &Game.ActiveScene->MissileList[i];
		/*if (Enemy->VertAccel >= 0.00f && Enemy->CheckFalling())
		{
			Enemy->move(vec2f(0.f, Enemy->VertAccel));
			Enemy->VertAccel += accY;
		}*/
		// Move the missile
		Missile->move(Missile->MovingVector * timemod);
		// Check collision with the enemies
		if (Missile->Owner == cOwner::Player)
		{
			//sf::FloatRect MissileRect(Missile->pos() - Missile->center(), Missile->size());
			for (cEnemy Enemy : Game.ActiveScene->EnemyList)
			{
				sf::FloatRect EnemyRect(Enemy.pos() - Enemy.center(), Enemy.size());
				if (EnemyRect.contains(Missile->pos()))
				{
					Game.ActiveScene->MissileList.remove(i);
					i -= 1;
					MissileRemoved = true;
					break;
				}
			}
		}
		// Check collision with the hero
		else if (Missile->Owner == cOwner::Enemy)
		{
			sf::FloatRect HeroRect(Game.Hero.pos() - Game.Hero.center(), Game.Hero.size());
			//sf::FloatRect MissileRect(Missile->pos() - Missile->center(), Missile->size());
			if (HeroRect.contains(Missile->pos()))
			{
				Game.ActiveScene->MissileList.remove(i);
				i -= 1;
				MissileRemoved = true;
			}
		}
		if (Missile->LifeTimerEnabled && !MissileRemoved)
		{
			Missile->LifeTimer -= timemod;
			if (Missile->LifeTimer <= 0.00f)
			{
				Game.ActiveScene->MissileList.remove(i);
				i -= 1;
				MissileRemoved = true;
			}
		}
	}
}