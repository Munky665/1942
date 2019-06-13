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

	stopDuration = (clock() - start) / (double)CLOCKS_PER_SEC;
	if (stopDuration < pauseTime && hasStopped != true)
	{
		pos.x = pos.x;
		pos.y = pos.y;
	}

	else if (stopDuration > pauseTime)
	{
		hasStopped = true;
		start = clock() - stopDuration;
		stopDuration = 0;
	}
}

void Enemy::WaitToFire() {
	waitDuration = (clock() - wait) / (double)CLOCKS_PER_SEC;
	if (waitDuration > fireWait) {
		hasFired = false;
		wait = clock() - waitDuration;
		waitDuration = 0;
		fireWait = rand() % 3 + 1;
	}
}
	