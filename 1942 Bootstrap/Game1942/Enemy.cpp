#include "Enemy.h"



Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Move(float deltaTime, int sW, int sH)
{

}

void Enemy::textureEnemy() 
{

}

void Enemy::Size() 
{

}

void Enemy::Reset(int sW, int sH) 
{

}

void Enemy::PauseFlight() 
{

	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	if (duration < pauseTime && hasStopped != true)
	{
		pos.x = pos.x;
		pos.y = pos.y;
	}

	else if (duration > pauseTime)
	{
		hasStopped = true;
		start = clock() - duration;
		duration = 0;
	}
}
	