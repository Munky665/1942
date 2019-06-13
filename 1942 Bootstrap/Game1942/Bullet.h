#pragma once
#include "Player.h"
#include "SmallShip.h"
class Bullet
{
	struct Position {
		float x, y;
		float w			= 10;
		float h			= 10;
	};

	
	float velocity		= 400;
	bool isSmall		= true;

	int bigDamage		= 10;
	int smallDamage		= 5;

public:
	int displacement	= 40;
	int damage			= 0;

	aie::Texture*		 texture;
	Position			 pos;
	
	Bullet();
	void PlayerFired(Player* p);
	void EnemyFired(Enemy* e);
	void Move(float deltaTime);
	void Reset();
	bool collided		= false;
	~Bullet();
	bool pfire			= false;
	bool efire			= false;
	bool exists			= false;
};

