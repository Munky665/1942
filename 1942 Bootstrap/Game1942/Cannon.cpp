#include "Cannon.h"



Cannon::Cannon(int i)
{
	for (int j = 0; j < maxBullets; ++j) {
		bullets.pushToEnd(new Bullet());
	}
	m_texture = new aie::Texture("./textures/Turret.png");

	destroyed = new aie::Texture("./textures/destroyed.png");
	
	m_renderer = new aie::Renderer2D();
	
	switch (i) {
	case 0:
		localTransform[2] = cannonOne;
		can1 = true;
		break;
	case 1:
		localTransform[2] = cannonTwo;
		outsideCannon = true;
		can2 = true;
		break;
	case 2:
		localTransform[2] = cannonThree;
		can3 = true;
		break;
	case 3:
		localTransform[2] = cannonFour;
		outsideCannon = true;
		can4 = true;
		break;
	}
	coll = new Collider();
	isAlive = true;
}
//moves cannons in place with the ship
void Cannon::Fire(float deltaTime, Player* p, DynamicArray<Bullet*> pB)
{
	if (inPosition == true)
	{
		if (isAlive == true)
		{
			hasFiredTimer();
			//fires bullets from cannons and checks bullet collisions with player
			CannonFired(deltaTime, p, pB);
			//allow player to take damage again
			p->immune = false;
		}
		else if (isAlive == false)
		{
			for (int i = 0; i < maxBullets; ++i)
			{
				bullets[i]->Reset();
			}
		}
	}
}


bool Cannon::hasFiredTimer()
{
	//fire rate count down.
	if (inPosition == true && isAlive == true) {
		duration = (clock() - wait) / (float)CLOCKS_PER_SEC;
		if (duration >= fireWait) {
			hasFired = false;
			wait = clock();
			sound = true;
			return true;
		}
	}
	else

		return false;
}
//fires bullets from cannons and checks bullet collisions with player
void Cannon::CannonFired(float deltaTime, Player * p, DynamicArray<Bullet*> pB)
{
	//check if boss has fired
	for (int i = 0; i < maxBullets; ++i)
	{
		if (hasFired == false && bullets[i]->exists == false) {
			bullets[i]->BossFired();
			bullets[i]->pos.x = localTransform[2].x;
			bullets[i]->pos.y = localTransform[2].y;
			bullets[i]->pos.y -= 20;
			hasFired = true;
		}
		//if bullet exists move towards bottom of screen at velocity
		if (bullets[i]->exists == true) {
			bullets[i]->pos.y -= velocity * deltaTime;
			//if bullet reaches bottom of screen reset
			if (bullets[i]->pos.y < 0) {
				bullets[i]->Reset();
			}
			//if bullet collides with player cause damage
			if (coll->Collision( p->pos, bullets[i]->pos) == true && bullets[i]->exists == true) {
				if (p->immune == false) {
					p->health = p->health - bullets[i]->damage;
				}
				p->immune = true;
				bullets[i]->exists = false;
				bullets[i]->efire = false;
			}
		}
		//reset bullet if exists not true
		if (bullets[i]->exists != true) {
			bullets[i]->Reset();
		}
		//check if player fire is hitting cannon
		Vector3 collider = pB[i]->pos - localTransform[2];
		float col = collider.magnitude();
		//remove bullet if it collides with cannon and do 1 point of damage
		if (pB[i]->exists == true) {
			if (col < 50) {
				pB[i]->exists = false;
				health -= 1;
			}
		}
		//if health is less than one destroy cannon
		if (health < 1 && isAlive == true) {
			isAlive = false;
 			p->score += score;
		}


	}
}

Cannon::~Cannon()
{
}
//draw cannons in positions
void Cannon::Draw(aie::Renderer2D* m_renderer)
{
;
	//draw not destroyed cannon
	if (isAlive == true) {
		m_renderer->drawSpriteTransformed3x3(m_texture, (float*)&localTransform, 0, 0, 49);
	}
	//draw destroyed cannon
	else if(isAlive == false) {
		m_renderer->drawSpriteTransformed3x3(destroyed, (float*)&localTransform, 0, 0, 49);
	}
	for (int i = 0; i < maxBullets; ++i) {
		if(bullets[i]->exists == true)
		m_renderer->drawSprite(bullets[i]->texture, bullets[i]->pos.x, bullets[i]->pos.y, 20, 20, 0, 49);
	}
}
//reset cannons position when game is reset
void Cannon::Reset(int i) {
	for (int i = 0; i < maxBullets; ++i)
	{
		bullets[i]->Reset();
	}
	can1 = false;
	can2 = false;
	can3 = false;
	can4 = false;
	switch (i) {
	case 0:
		localTransform[2] = cannonOne;
		can1 = true;
		break;
	case 1:
		localTransform[2] = cannonTwo;
		outsideCannon = true;
		can2 = true;
		break;
	case 2:
		localTransform[2] = cannonThree;
		can3 = true;
		break;
	case 3:
		localTransform[2] = cannonFour;
		outsideCannon = true;
		can4 = true;
		break;
	}
	isAlive = true;
	inPosition = false;
	left = false;
	right = false;
	health = maxHealth;
}