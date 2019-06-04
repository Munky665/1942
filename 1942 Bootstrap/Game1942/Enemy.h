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
	

	
	float sWidth = 1280;
	float sHeight = 720;
	float speed = 300;
	float topSpawn = rand() % 740 + 720;
	float firstSpawn = rand() % 1280 + 1;
	bool collided = false;
	Position pos { firstSpawn, topSpawn};
	
	aie::Texture* texture;
	virtual void Move(float deltaTime);
	virtual void textureEnemy();
	virtual void Size();
	Enemy();
	~Enemy();
};

