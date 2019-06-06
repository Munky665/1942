#include "BigShip.h"



BigShip::BigShip()
{
	Size();
	textureEnemy();
	scoreValue = 40;
}


BigShip::~BigShip()
{
}

void BigShip::Move(float deltaTime) {
	
	pos.y -= (speed + BigPlaneBooster) 
			 * deltaTime;

	if (pos.y < 0) {
		pos.x = rand() % 1280 + 1;
		pos.y = sHeight;
	}
}

void BigShip::textureEnemy() {
	texture = new aie::Texture("./textures/BigPlane.png");
}

void BigShip::Size() {
	pos.h = 80;
	pos.w = 80;
}