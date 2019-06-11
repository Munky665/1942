#pragma once
#include "Background.h"
#include "Bullet.h"


class Collider
{
public:
	//checks if background items are in the same place
	bool Collision(Background sprite_1, Background sprite_2);
	//checks if player has collided with an enemy
	bool Collision(Player* player, Enemy* enemy, int size);
	//checks if bullet has collided with enemy
	bool Collision(Bullet* b, Enemy* enemy, int size);
	//checks if bullet has collided with player
	bool Collision(Bullet* b, Player* p);
	int screenWidth  = 1280;
	int screenHeight = 720;
	int displacment  = 100;
	Collider();
	~Collider();
};

