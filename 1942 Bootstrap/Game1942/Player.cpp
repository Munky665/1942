#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}


void Player::Move(aie::Input* input, float deltaTime) {
	
	if (input->isKeyDown(aie::INPUT_KEY_LEFT) && input->isKeyDown(aie::INPUT_KEY_UP))
	{
	pos.x -= speed * deltaTime;
	pos.y += speed * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_UP) && input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
	pos.x += speed * deltaTime;
	pos.y += speed * deltaTime;
	}
	else if (input->isKeyDown(aie::INPUT_KEY_RIGHT) && input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
	pos.x += speed * deltaTime;
	pos.y -= speed * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_DOWN) && input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
	pos.x -= speed * deltaTime;
	pos.y -= speed * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_RIGHT)) 
	{
		 pos.x += speed * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		 pos.x -= speed * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_UP))
	{
		 pos.y += speed * deltaTime;
	}


	else if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		 pos.y -= speed * deltaTime;
	}
	
	
}

void Player::Stop() {
	if (pos.x > sWidth - sBuffer) {
		pos.x = sWidth - sBuffer;
	}
	else if (pos.y > sHeight - sBuffer ) {
		pos.y = sHeight - sBuffer;
	}
	if (pos.x < sBuffer) {
		pos.x = sBuffer;
	}
	if (pos.y < sBuffer) {
		pos.y = sBuffer;
	}
}
