#include "Collider.h"



Collider::Collider()
{
}


Collider::~Collider()
{
}

bool Collider::BkgCollision(Vector3 objOne, Vector3 objTwo)
{
	Vector3 collider = objTwo - objOne;
	float col = collider.magnitude();
			//The backgrounds appear to overlap.
	if (col < 299) {
		return true;
	}
	else
	{
		return false;
	}
}

bool Collider::Collision(Vector3 player, Vector3 enemy)
{
	Vector3 collider = player - enemy;
	float col = collider.magnitude();

	if (col < 50) {
		return true;
	}
	else
	{
		return false;
	}
}



//checks player vs enemy collisions
bool Collider::CheckPVECollision(Player* p, Enemy* e)
{
		if (Collision(p->pos, e->pos) == true && p->immune == false)
		{
			p->immune = true;
			p->health -= e->crashDamage;
			p->score = p->score + e->scoreValue;
			e->isAlive = false;
			return true;
		}
		return false;
}
//checks player bullet vs enemy collisions
bool Collider::CheckBVECollision(DynamicArray<Bullet*> b, Enemy* e, int bs, Player* p)
{
	for (int j = 0; j < bs; j++)
	{
		if (Collision(b[j]->pos, e->pos) == true && e->isAlive == true)
		{  
				p->score = p->score + e->scoreValue;
				e->isAlive = false;
				b[j]->collided = true;
				return true;
		}
	}
	return false;
}
//checks enemy bullet vs player collisions 
bool Collider::CheckBVPCollision(DynamicArray<Bullet*> b, Player* p, int size)
{
	for (int i = 0; i < size; ++i) {
		if (b[i]->exists == true) {
			if (b[i]->collided == false && Collision(b[i]->pos, p->pos) == true)
			{
				if (p->immune == false) {
					p->health -= b[i]->damage;
					p->immune = true;
					b[i]->exists = false;
					b[i]->efire = false;
					b[i]->collided = true;
					return true;
				}
			}
		}
	}
	return false;
}
