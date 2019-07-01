#include "Cannon.h"



Cannon::Cannon(int i)
{
	for (int j = 0; j < maxBullets; ++j) {
		bullets.push_back(new Bullet());
	}
	m_texture = new aie::Texture("./textures/Turret.png");

	destroyed = new aie::Texture("./textures/destroyed.png");
	
	m_renderer = new aie::Renderer2D();
	
	switch (i) {
	case 0:
		cannonPosition = cannonOne;
		can1 = true;
		break;
	case 1:
		cannonPosition = cannonTwo;
		outsideCannon = true;
		can2 = true;
		break;
	case 2:
		cannonPosition = cannonThree;
		can3 = true;
		break;
	case 3:
		cannonPosition = cannonFour;
		outsideCannon = true;
		can4 = true;
		break;
	}
	col = new Collider();
}
void Cannon::Move(float deltaTime, Player* p, std::vector<Bullet*> pB)
{
	if (inPosition == false) {
		if (outsideCannon == false) {
			vector3 downDistance = stoppingPointOne - cannonPosition;
			downDistance.x = 0;
			magOne = downDistance.magnitued();

			if (magOne > 0) {
				cannonPosition += downDistance.normalise(downDistance) * 2;
			}
			else if (magOne < 1)
			{
				right = true;
				inPosition = true;
			}
		}
		else if (outsideCannon == true) {

			vector3 downDistance = stoppingPointTwo - cannonPosition;
			downDistance.x = 0;
			magOne = downDistance.magnitued();

			if (magOne > 1) {
				cannonPosition += downDistance.normalise(downDistance) * 2;
			}
			else if (magOne < 2)
			{
				right = true;
				inPosition = true;
			}
		}
	}
	if (right == true)
	{
		if (outsideCannon == false) {
			if (can3 == true) {
				vector3 rightDistance = rightscreenC - cannonPosition;
				rightDistance.y = 0;
				magOne = rightDistance.magnitued();

				if (magOne > 0) {
					cannonPosition += rightDistance.normalise(rightDistance) * 2;
				}
				else if (magOne < 1)
				{
					right = false;
					left = true;
				}
			}
			else if (can1 == true) {
				vector3 rightDistance = rightscreenC - cannonPosition;
				rightDistance.y = 0;
				magOne = rightDistance.magnitued();

				if (magOne > 500) {
					cannonPosition += rightDistance.normalise(rightDistance) * 2;
				}
				else if (magOne < 501)
				{
					right = false;
					left = true;
				}
			}
		}
		else if (outsideCannon == true) {
			if (can4 == true) {
				vector3 rightDistance = rightscreenC2 - cannonPosition;
				rightDistance.y = 0;
				magOne = rightDistance.magnitued();

				if (magOne > 0) {
					cannonPosition += rightDistance.normalise(rightDistance) * 2;
				}
				else if (magOne < 1)
				{
					right = false;
					left = true;
				}
			}
			else if (can2 == true) {
				vector3 rightDistance = rightscreenC2 - cannonPosition;
				rightDistance.y = 0;
				magOne = rightDistance.magnitued();

				if (magOne > 936) {
					cannonPosition += rightDistance.normalise(rightDistance) * 2;
				}
				else if (magOne < 937)
				{
					right = false;
					left = true;
				}
			}
		}
	}
	if (left == true)
	{
		if (outsideCannon == false) {
			if (can1 == true) {
				vector3 leftDistance = leftscreenC - cannonPosition;
				leftDistance.y = 0;
				magOne = leftDistance.magnitued();

				if (magOne > 0) {
					cannonPosition += leftDistance.normalise(leftDistance) * 2;
				}
				else if (magOne < 1)
				{
					right = true;
					left = false;
				}
			}
			else if (can3 == true) {
				vector3 leftDistance = leftscreenC - cannonPosition;
				leftDistance.y = 0;
				magOne = leftDistance.magnitued();

				if (magOne > 500) {
					cannonPosition += leftDistance.normalise(leftDistance) * 2;
				}
				else if (magOne < 501)
				{
					right = true;
					left = false;
				}
			}
		}
		if (outsideCannon == true) {
			if (can2 == true) {
				vector3 leftDistance = leftscreenC2 - cannonPosition;
				leftDistance.y = 0;
				magOne = leftDistance.magnitued();

				if (magOne > 0) {
					cannonPosition += leftDistance.normalise(leftDistance) * 2;
				}
				else if (magOne < 1)
				{
					right = true;
					left = false;
				}
			}
			else if (can4 == true) {
				vector3 leftDistance = leftscreenC2 - cannonPosition;
				leftDistance.y = 0;
				magOne = leftDistance.magnitued();

				if (magOne > 936) {
					cannonPosition += leftDistance.normalise(leftDistance) * 2;
				}
				else if (magOne < 937)
				{
					right = true;
					left = false;
				}
			}
		}
	}
	if (inPosition == true && isAlive == true) {

		duration = (clock() - wait) / (float)CLOCKS_PER_SEC;
		if (duration > fireWait) {
			hasFired = false;
			wait = clock() - duration;
			duration = 0;
		}
		else
			hasFired = true;

		for (int i = 0; i < maxBullets; ++i) {
			if (hasFired == false && bullets[i]->exists == false) {
				bullets[i]->BossFired();
				bullets[i]->pos.x = cannonPosition.x;
				bullets[i]->pos.y = cannonPosition.y;
				bullets[i]->pos.y - 20;
			}
			if (bullets[i]->exists == true) {
				bullets[i]->pos.y -= velocity * deltaTime;
				if (bullets[i]->pos.y < 0) {
					bullets[i]->Reset();
				}
				if (col->Collision(bullets[i], p) == true && bullets[i]->exists == true) {
					if (p->immune == false) {
						p->health = p->health - bullets[i]->damage;
					}
					p->immune = true;
					bullets[i]->exists = false;
					bullets[i]->efire = false;
				}
			}
			if (bullets[i]->exists != true) {
				bullets[i]->Reset();
			}
			vector3 collider = pB[i]->pos - cannonPosition;
			float col = collider.magnitued();
			if (col < 50) {
				pB[i]->exists = false;
 				health -= 1;
			}
			if (health < 1) {
				isAlive = false;
			}

		}
		p->immune = false;
	}
}



Cannon::~Cannon()
{
}
void Cannon::Draw()
{

	m_renderer->begin();
	if (isAlive == true) {
		m_renderer->drawSprite(m_texture, cannonPosition.x, cannonPosition.y, 0, 0, 0, 50);
	}
	else if(isAlive == false) {
		m_renderer->drawSprite(destroyed, cannonPosition.x, cannonPosition.y, 0, 0, 0, 50);
	}
	for (int i = 0; i < maxBullets; ++i) {
		if(bullets[i]->exists == true)
		m_renderer->drawSprite(bullets[i]->texture, bullets[i]->pos.x, bullets[i]->pos.y, 20, 20, 0, 50);
	}
	m_renderer->end();
}

void Cannon::Reset(int i) {
	inPosition = false;
	switch (i) {
	case 0:
		cannonPosition = cannonOne;
		can1 = true;
		break;
	case 1:
		cannonPosition = cannonTwo;
		outsideCannon = true;
		can2 = true;
		break;
	case 2:
		cannonPosition = cannonThree;
		can3 = true;
		break;
	case 3:
		cannonPosition = cannonFour;
		outsideCannon = true;
		can4 = true;
		break;
	}
}