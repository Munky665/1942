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
	isAlive = true;
}
//moves cannons in place with the ship
void Cannon::Move(float deltaTime, Player* p, DynamicArray<Bullet*> pB)
{
	if (inPosition == false) {
		//sets inside cannon position on plane wings
		if (outsideCannon == false) {
			vector2 downDistance = stoppingPointOne - cannonPosition;
			downDistance.x = 0;
			magOne = downDistance.magnitued();
		//if distance from y position less than 1 unit
		if (magOne < 1)
		{
			right = true;
			inPosition = true;
		}
		//if distance from y position greater than 1 unit
		else if (magOne > 0) {
				cannonPosition += downDistance.normalise(downDistance) * 200 * deltaTime;
			}

		}
		//set outside cannon position on plane wings
		else if (outsideCannon == true) 
		{
			vector2 downDistance = stoppingPointTwo - cannonPosition;
			downDistance.x = 0;
			magOne = downDistance.magnitued();
			//if distance from y position greater than 1 unit
			if (magOne < 1)
			{
				right = true;
				inPosition = true;
			}
			//if distance from y position less than 1 unit
			else if (magOne > 0) {
				cannonPosition += downDistance.normalise(downDistance) * 200 * deltaTime;
			}

		}
	}
	//once inposition move cannons with boss to the right.
	if (right == true)
	{
		if (outsideCannon == false) {
			if (can3 == true) {
				vector2 rightDistance = rightscreenC - cannonPosition;
				rightDistance.y = 0;
				magOne = rightDistance.magnitued();
				//if distance from right side less than one
				if (magOne < 1)
				{
					right = false;
					left = true;
				}
				//if distance from right side greater than one
				else if (magOne > 0) {
					cannonPosition += rightDistance.normalise(rightDistance) * 200 * deltaTime;
				}

			}
			else if (can1 == true) {
				vector2 rightDistance = rightscreenC - cannonPosition;
				rightDistance.y = 0;
				magOne = rightDistance.magnitued();

				if (magOne < 501)
				{
					right = false;
					left = true;
				}

				else if (magOne > 500) {
					cannonPosition += rightDistance.normalise(rightDistance) * 200 * deltaTime;
				}

			}
		}
		else if (outsideCannon == true) {
			if (can4 == true) {
				vector2 rightDistance = rightscreenC2 - cannonPosition;
				rightDistance.y = 0;
				magOne = rightDistance.magnitued();

				if (magOne <= 1)
				{
					right = false;
					left = true;
				}

				else if (magOne > 0) {
					cannonPosition += rightDistance.normalise(rightDistance) * 200 * deltaTime;
				}

			}
			else if (can2 == true) {
				vector2 rightDistance = rightscreenC2 - cannonPosition;
				rightDistance.y = 0;
				magOne = rightDistance.magnitued();
				if (magOne < 937)
				{
					right = false;
					left = true;
				}

				else if (magOne > 936) {
					cannonPosition += rightDistance.normalise(rightDistance) * 200 * deltaTime;
				}

			}
		}
	}
	//once in position move cannons with boss to the left
	if (left == true)
	{
		if (outsideCannon == false) {
			if (can1 == true) {
				vector2 leftDistance = leftscreenC - cannonPosition;
				leftDistance.y = 0;
				magOne = leftDistance.magnitued();

				if (magOne < 1)
				{
					right = true;
					left = false;
				}

				else if (magOne > 0) {
					cannonPosition += leftDistance.normalise(leftDistance) * 200 * deltaTime;
				}

			}
			else if (can3 == true) {
				vector2 leftDistance = leftscreenC - cannonPosition;
				leftDistance.y = 0;
				magOne = leftDistance.magnitued();
				if (magOne < 501)
				{
					right = true;
					left = false;
				}

				else if (magOne > 500) {
					cannonPosition += leftDistance.normalise(leftDistance) * 200 * deltaTime;
				}

			}
		}
		if (outsideCannon == true) {
			if (can2 == true) {
				vector2 leftDistance = leftscreenC2 - cannonPosition;
				leftDistance.y = 0;
				magOne = leftDistance.magnitued();
				if (magOne < 1)
				{
					right = true;
					left = false;
				}

				else if (magOne > 0) {
					cannonPosition += leftDistance.normalise(leftDistance) * 200 * deltaTime;
				}

			}
			else if (can4 == true) {
				vector2 leftDistance = leftscreenC2 - cannonPosition;
				leftDistance.y = 0;
				magOne = leftDistance.magnitued();
				if (magOne < 937)
				{
					right = true;
					left = false;
				}

				else if (magOne > 935) {
					cannonPosition += leftDistance.normalise(leftDistance) * 200 * deltaTime;
				}

			}
		}
	}
	if (isAlive == true) {
		//fire rate count down.
		if (inPosition == true && isAlive == true) {
			duration = (clock() - wait) / (float)CLOCKS_PER_SEC;
			if (duration >= fireWait) {
				hasFired = false;
				wait = clock();
			}

			//fires bullets from cannons and checks bullet collisions with player
			CannonFired(deltaTime, p, pB);
			//allow player to take damage again
			p->immune = false;
		}
	}
	else if (isAlive == false) {
		for (int i = 0; i < maxBullets; ++i) {
			bullets[i]->Reset();
		}
	}
}
//fires bullets from cannons and checks bullet collisions with player
void Cannon::CannonFired(float deltaTime, Player * p, DynamicArray<Bullet*> pB)
{
	//check if boss has fired
	for (int i = 0; i < maxBullets; ++i)
	{
		if (hasFired == false && bullets[i]->exists == false) {
			bullets[i]->BossFired();
			bullets[i]->pos.x = cannonPosition.x;
			bullets[i]->pos.y = cannonPosition.y;
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
			if (col->Collision(bullets[i]->pos, p->pos) == true && bullets[i]->exists == true) {
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
		vector2 collider = pB[i]->pos - cannonPosition;
		float col = collider.magnitued();
		//remove bullet if it collides with cannon and do 1 point of damage
		if (col < 50) {
			pB[i]->exists = false;
			health -= 1;
		}
		//if health is less than one destroy cannon
		if (health < 1) {
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
		m_renderer->drawSprite(m_texture, cannonPosition.x, cannonPosition.y, 0, 0, 0, 50);
	}
	//draw destroyed cannon
	else if(isAlive == false) {
		m_renderer->drawSprite(destroyed, cannonPosition.x, cannonPosition.y, 0, 0, 0, 50);
	}
	for (int i = 0; i < maxBullets; ++i) {
		if(bullets[i]->exists == true)
		m_renderer->drawSprite(bullets[i]->texture, bullets[i]->pos.x, bullets[i]->pos.y, 20, 20, 0, 50);
	}
}
//reset cannons position when game is reset
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