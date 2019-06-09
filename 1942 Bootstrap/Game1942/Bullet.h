#pragma once
#include "Player.h"
#include "SmallShip.h"
class Bullet
{
	struct Position {
		float x, y;
		float w = 10;
		float h = 10;
	};

	int displacement = 40;
	float velocity = 250;
	bool isSmall = true;
	bool pfire = false;
	bool efire = false;
public:
	aie::Texture* texture;
	Position pos;
	Bullet();
	Bullet(Player* p);
	Bullet(Enemy e);
	void Move(float deltaTime);
	bool collided = false;
	~Bullet();

	bool exists = false;
};

