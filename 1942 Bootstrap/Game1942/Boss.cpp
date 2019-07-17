#include "Boss.h"



Boss::Boss(float x, float y)
{
	texture = new aie::Texture("./textures/BossBase.png");
	renderer = new aie::Renderer2D();
	pos.x = x;
	pos.y = y;
}


Boss::~Boss()
{
}

void Boss::FlyIn(float deltaTime)
{
	if (pos.y < 360)
	{
		pos.x = pos.x;
		pos.y = pos.y;
	}
	else
	{
		pos.y -= speed * deltaTime;
	}
}