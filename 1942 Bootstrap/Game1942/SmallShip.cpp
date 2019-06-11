#include "SmallShip.h"



SmallShip::SmallShip()
{
	Size();
	textureEnemy();
	scoreValue = 20;
	isAlive = true;
}


SmallShip::~SmallShip()
{
}

void SmallShip::Move(float deltaTime, int sW, int sH)
{
	switch (temp) 
	{
	case 1:
		pos.x -= speed * deltaTime;
		pos.y -= speed * deltaTime;
		break;
	case 2:
		pos.x += speed * deltaTime;
		pos.y -= speed * deltaTime;
		break;
	default:
		pos.x -= speed * deltaTime;
		pos.y -= speed * deltaTime;
		break;
	}
	

	if (pos.x < 0 || pos.x > sW) {
		pos.x = rand() % sW + 1;
		pos.y = sH;
		temp = rand() % 2 + 1;
		
		
	}
}

void SmallShip::textureEnemy() 
{
	texture = new aie::Texture("./textures/Smallplane.png");
}

void SmallShip::Size() 
{
	pos.h = 64;
	pos.w = 64;
}

void SmallShip::Reset(int sW, int sH) 
{
	pos.x = rand() % sW + 1;
	pos.y = sH;
	temp = rand() % 2 + 1;
	isAlive = true;
	hasFired = false;
	hasStopped = false;
}