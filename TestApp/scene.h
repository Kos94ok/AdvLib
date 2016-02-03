
#include "stdafx.h"
#include "unit.h"

class cScene
{
public:
	bool Visible = false;

	adv::vectox<cUnit> UnitList;
	adv::vectox<cEnemy> EnemyList;
	adv::vectox<cMissile> MissileList;

	void paint(sf::RenderTexture* texHandle, sf::Transform matrix = sf::Transform())
	{
		UnitList.lock();
		for (int i = 0; i < (int)UnitList.size(); i++)
		{
			UnitList[i].paint(texHandle, matrix);
		}
		UnitList.unlock();
		EnemyList.lock();
		for (int i = 0; i < (int)EnemyList.size(); i++)
		{
			EnemyList[i].paint(texHandle, matrix);
		}
		EnemyList.unlock();
		MissileList.lock();
		for (int i = 0; i < (int)MissileList.size(); i++)
		{
			MissileList[i].paint(texHandle, matrix);
		}
		MissileList.unlock();
	}
};