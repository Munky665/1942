#include "Background.h"



Background::Background()
{
}


Background::~Background()
{
}

void Background::Move(float deltaTime , float speed)
{
	pos.y -= speed * deltaTime;

	if (pos.y <= -100)
	{
		pos.y = topSpawn;
		pos.x = rand() % 1280 + 1;
	}
}



