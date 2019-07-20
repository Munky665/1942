#pragma once
#include "Background.h"
#include "HealthPickUp.h"
#include "Bullet.h"
#include "DynamicArray.h"


class Collider
{
public:
	//checks if background items are in the same place
	bool Collision(Background* bg1, Background* bg2);
	//checks if player has collided with an enemy
	bool Collision(Player* player, Enemy* enemy, int size);
	//checks if bullet has collided with enemy
	bool Collision(Bullet* b, Enemy* enemy, int size);
	//checks if bullet has collided with player
	bool Collision(Bullet* b, Player* p);
	//checks if Health is picked up by player
	bool Collision(HealthPickUp* b, Player* p);

	void CheckPVECollision(Player* p, Enemy* e, int s);
	void CheckBVECollision(DynamicArray<Bullet*> b, Enemy* e, int bs, int es, Player* p);
	void CheckBVPCollision(DynamicArray<Bullet*> b, Player* p, int size);
	int screenWidth  = 1280;
	int screenHeight = 720;
	int displacment  = 100;
	Collider();
	~Collider();
};

