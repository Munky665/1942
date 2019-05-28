#include "Background.h"



Background::Background()
{
}


Background::~Background()
{
}

void Background::Move(float deltaTime) {
	pos.y -= speed * deltaTime;

	if (pos.y <= -40) {
		pos.y = topSpawn;
		pos.x = rand() % 1280 + 1;
	}
}

