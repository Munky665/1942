#include "SmallShip.h"



SmallShip::SmallShip()
{
	Size();
	textureEnemy();
	scoreValue = 20;
}


SmallShip::~SmallShip()
{
}

void SmallShip::Move(float deltaTime) {
	switch (temp) {
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
	

	if (pos.x < 0 || pos.x > sWidth) {
		pos.x = rand() % 1280 + 1;
		pos.y = sHeight;
		temp = rand() % 2 + 1;
		
		
	}
}

void SmallShip::textureEnemy() {
	texture = new aie::Texture("./textures/Smallplane.png");
}

void SmallShip::Size() {
	pos.h = 64;
	pos.w = 64;
}