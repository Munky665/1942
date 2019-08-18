#pragma once
#include "Player.h"
#include "SmallShip.h"
#include <MathLib.h>
class Bullet
{


	
	float velocity		= 400;
	bool isSmall		= true;
	int smallsize		= 15;
	int bigsize			= 20;
	int bigDamage		= 10;
	int smallDamage		= 5;

public:
	int displacement	= 40;
	int damage			= 0;

	aie::Texture*		 texture;
	Vector3 pos = { 0,0,0 };
	float size = 15;
	Bullet();
	void PlayerFired(Player* p);
	void EnemyFired(Enemy* e);
	void Move(float deltaTime);
	void Reset();
	void BossFired();
	bool collided		= false;
	~Bullet();
	bool pfire			= false;
	bool efire			= false;
	bool exists			= false;
};

