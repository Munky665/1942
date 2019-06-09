#pragma once
#include "Background.h"
#include "Bullet.h"


class Collider
{
public:
	bool Collision(Background sprite_1, Background sprite_2);
	bool Collision(Player* sprite_1, Enemy sprite_2);
	bool Collision(Player* player, Enemy enemy[], int size);
	bool Collision(Bullet* b, Enemy enemy[], int size);
	bool Collision(Bullet* b, Player* p);
	int screenWidth = 1280;
	int screenHeight = 720;
	int displacment = 100;
	Collider();
	~Collider();
};

