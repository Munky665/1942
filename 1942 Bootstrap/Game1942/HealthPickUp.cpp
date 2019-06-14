#include "HealthPickUp.h"



HealthPickUp::HealthPickUp()
{
	texture = new aie::Texture("./textures/healthpickup.png");
	renderer = new aie::Renderer2D();
}


HealthPickUp::~HealthPickUp()
{
}

void HealthPickUp::Move(float deltaTime) 
{
	if (exists == true) {
		pos.y -= travelSpeed * deltaTime;

		if (pos.y < 0) {
			exists = false;
		}
	}
}

void HealthPickUp::SpawnHealth(float x, float y) 
{
	temp = rand() % 100 + 1;
	if (temp == 6 && exists == false) {
		exists = true;
		pos.x = x;
		pos.y = y;
	}

}
void HealthPickUp::Draw() 
{
	if (exists == true)
	{
		renderer->begin();
		renderer->drawSprite(texture, pos.x, pos.y, pos.w, pos.h, 0, 49);
		renderer->end();
	}
}

void HealthPickUp::DeActivate()
{
	exists = false;
}
