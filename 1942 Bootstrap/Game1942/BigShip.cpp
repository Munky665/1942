#include "BigShip.h"



BigShip::BigShip()
{
	Size();
	textureEnemy();
	scoreValue = 40;
	isAlive = true;
	isBig = true;
}


BigShip::~BigShip()
{
}

void BigShip::Move(float deltaTime, int sW, int sH) {
	
	pos.y -= (speed + BigPlaneBooster) 
			 * deltaTime;

	if (pos.y < 0) {
		pos.x = respwan;
		pos.y = sH;
	}
}

void BigShip::textureEnemy() {
	texture = new aie::Texture("./textures/BigPlane.png");
}

void BigShip::Size() {
	pos.h = 80;
	pos.w = 80;
}

void BigShip::Reset(int sW, int sH) {
	pos.x = respwan;
	pos.y = sH;
	isAlive = true;
	hasFired = false;
	hasStopped = false;
}