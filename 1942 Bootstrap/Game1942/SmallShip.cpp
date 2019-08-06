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
	//sets angle of flight
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
	
	//when small ship reaches bottom of screen, reset to top of screen
	if (pos.x < 0 || pos.x > sW) {
		Reset(sW, sH);
		
		
	}
}

void SmallShip::textureEnemy() 
{
	texture = new aie::Texture("./textures/Smallplane.png");
}

//sets small ships width and height.
void SmallShip::Size() 
{
	size.y = 64;
	size.x = 64;
}
//resets small ship to random position on at the top of the screen 
void SmallShip::Reset(int sW, int sH) 
{
	topSpawn = rand() % 740 + 720;
	firstSpawn = rand() % 1280 + 1;

	pos.x = firstSpawn;
	pos.y = topSpawn;
	temp = rand() % 2 + 1;
	isAlive = true;
	hasFired = false;
	hasStopped = false;
	collided = false;
}