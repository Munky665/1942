#include "Bullet.h"



Bullet::Bullet()
{

}
//constructor for player bullets
Bullet::Bullet(Player* p)
{
	pos.x = p->pos.x;
	pos.y = p->pos.y + displacement;
	texture = new aie::Texture("./textures/bullet.png");
	exists = true;
	pfire = true;
}
//constructor for Enemy Bullets
Bullet::Bullet(Enemy* e)
{
	pos.x = e->pos.x;
	pos.y = e->pos.y + displacement;
	texture = new aie::Texture("./textures/bullet.png");
	exists = true;
	efire = true;
}

Bullet::~Bullet()
{
}

void Bullet::Move(float deltaTime) {
	if (pfire == true) {
		pos.y += velocity * deltaTime;
	}
	else if (efire == true) {
		pos.y -= velocity * deltaTime;
	}
}