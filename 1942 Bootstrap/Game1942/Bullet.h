#pragma once
#include "Player.h"
#include "SmallShip.h"
#include "Vector2.h"
class Bullet
{


	
	float velocity		= 400;
	bool isSmall		= true;

	int bigDamage		= 10;
	int smallDamage		= 5;

public:
	int displacement	= 40;
	int damage			= 0;

	aie::Texture*		 texture;
	vector2 pos = { 0,0 };
	float size = 10;
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

