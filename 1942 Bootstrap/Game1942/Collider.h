#pragma once
#include "Background.h"
#include "HealthPickUp.h"
#include "Bullet.h"
#include "DynamicArray.h"



class Collider
{


public:
	//checks if background items are in the same place
	bool BkgCollision(Vector3 objOne, Vector3 objTwo);
	//checks if player has collided with an enemy
	bool Collision(Vector3 player, Vector3 enemy);

	bool CheckPVECollision(Player* p, Enemy* e);
	bool CheckBVECollision(DynamicArray<Bullet*> b, Enemy* e, int bs, Player* p);
	bool CheckBVPCollision(DynamicArray<Bullet*> b, Player* p, int size);
	int screenWidth  = 1280;
	int screenHeight = 720;
	int displacment  = 100;
	float size = 45;
	float landSize = 299;

	Collider();
	~Collider();
};

