#pragma once
#include "Background.h"
#include "HealthPickUp.h"
#include "Bullet.h"
#include "DynamicArray.h"


class Collider
{
public:
	//checks if background items are in the same place
	bool BkgCollision(vector2 objOne, vector2 objTwo);
	//checks if player has collided with an enemy
	bool Collision(vector2 player, vector2 enemy);

	void CheckPVECollision(Player* p, Enemy* e);
	void CheckBVECollision(DynamicArray<Bullet*> b, Enemy* e, int bs, Player* p);
	void CheckBVPCollision(DynamicArray<Bullet*> b, Player* p, int size);
	int screenWidth  = 1280;
	int screenHeight = 720;
	int displacment  = 100;
	float size = 45;
	float landSize = 299;
	Collider();
	~Collider();
};

