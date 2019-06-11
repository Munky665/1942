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

void Bullet::EnemyFired(Enemy* e) 
{
	exists = true;
	efire = true;
	pos.x = e->pos.x;
	pos.y = e->pos.y - displacement;
	e->hasFired = true;

	if (e->isBig == true & pos.h == 10 && pos.w == 10) 
	{
		if (pos.h == 10 && pos.w == 10) 
		{
			pos.h += 10;
			pos.w += 10;
		}
		damage = bigDamage;
	}
	else if(e->isBig != true && pos.h > 10 && pos.w > 10)
	{
		pos.h = 10;
		pos.w = 10;
		damage = smallDamage;
	}
	else 
	{
		damage = smallDamage;
	}
}