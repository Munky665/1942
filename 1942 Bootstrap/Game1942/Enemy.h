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
	clock_t start		= clock();
	clock_t wait        = clock();
	double stopDuration	= 0;
	double waitDuration	= 0;
	double fireWait		= 4;
	double pauseTime	= 5;
	float scoreValue	= 0;
	float sWidth		= 1280;
	float sHeight		= 720;
	float speed			= 300;
	float maxFired		= 4;
	float topSpawn		= rand() % 740 + 720;
	float firstSpawn	= rand() % 1280 + 1;
	bool collided		= false;
	bool hasFired		= false;
	bool isAlive		= false;

	Position pos{ firstSpawn, topSpawn };
	
	int crashDamage		= 20;
	
	aie::Texture* texture;

	virtual void Move(float deltaTime, int sW, int sH);
	virtual void textureEnemy();
	virtual void Size();
	virtual void Reset(int sW, int sH);
	void WaitToFire();
	void PauseFlight();
	bool isBig = false;
	bool hasStopped;
	Enemy();
	~Enemy();
};