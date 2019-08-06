#include "Bullet.h"



Bullet::Bullet()
{
	texture = new aie::Texture("./textures/bullet.png");
}

Bullet::~Bullet()
{
}

void Bullet::Move(float deltaTime)
{
	if (pfire == true)
	{
		pos.y += velocity * deltaTime;
	}
	else if (efire == true)
	{
		pos.y -= velocity * deltaTime;
	}
}

void Bullet::PlayerFired(Player* p)
{
	exists = true;
	pfire = true;
	pos.x = p->pos.x;
	pos.y = p->pos.y + displacement;
	p->playerFired = true;
}

void Bullet::BossFired() {
	exists = true;
	efire = true;
	damage = bigDamage;
}

void Bullet::EnemyFired(Enemy* e) 
{
	exists = true;
	efire = true;
	collided = false;
	pos.x = e->pos.x;
	pos.y = e->pos.y - displacement;

	if (e->isBig == true & size == smallsize) 
	{
		if (size == smallsize) 
		{
			size = bigsize;
		}
		damage = bigDamage;
	}
	else if(e->isBig != true && size > smallsize )
	{
		size = smallsize;
		damage = smallDamage;
	}
	else 
	{
		damage = smallDamage;
	}
}

void Bullet::Reset() {
	pos = pos;
	pfire = false;
	efire = false;
	exists = false;
}