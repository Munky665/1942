#pragma once

#include "Player.h"
#include <time.h>
#include <random>
class Enemy
{
public:
	
	virtual struct Position {
		float x, y;
		float h;
		float w;
		
	}; 
	

	float scoreValue = 0;
	float sWidth = 1280;
	float sHeight = 720;
	float speed = 300;
	float fired = 0;
	float maxFired = 4;
	float topSpawn = rand() % 740 + 720;
	float firstSpawn = rand() % 1280 + 1;
	bool collided = false;
	bool hasFired = false;
	bool isAlive = false;
	Position pos { firstSpawn, topSpawn};
	
	aie::Texture* texture;
	virtual void Move(float deltaTime);
	virtual void textureEnemy();
	virtual void Size();
	Enemy* Allocate(Enemy enemy[], int size);
	Enemy();
	~Enemy();
};

