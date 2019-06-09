#include "Collider.h"



Collider::Collider()
{
}


Collider::~Collider()
{
}

bool Collider::Collision(Background sprite_1, Background sprite_2) {
	//If the leftmost or rightmost point of the first sprite lies somewhere inside the second, continue.
	if ((sprite_1.pos.x >= sprite_2.pos.x && sprite_1.pos.x <= (sprite_2.pos.x + sprite_2.pos.w)) ||
		((sprite_1.pos.x + sprite_1.pos.w) >= sprite_2.pos.x && (sprite_1.pos.x + sprite_1.pos.w) <= (sprite_2.pos.x + sprite_2.pos.w))) {
		//Now we look at the y axis:
		if ((sprite_1.pos.y >= sprite_2.pos.y && sprite_1.pos.y <= (sprite_2.pos.y + sprite_2.pos.h)) ||
			((sprite_1.pos.y + sprite_1.pos.h) >= sprite_2.pos.y && (sprite_1.pos.y + sprite_1.pos.h) <= (sprite_2.pos.y + sprite_2.pos.h))) {
			//The sprites appear to overlap.
			return true;
		}
	}
	//The sprites do not overlap:
	return false;
}

bool Collider::Collision(Player* player, Enemy enemy) {
	//If the leftmost or rightmost point of the first sprite lies somewhere inside the second, continue.
	if	((player->pos.x >= enemy.pos.x && player->pos.x <= (enemy.pos.x + enemy.pos.w)) ||
		((player->pos.x + player->pos.w) >= enemy.pos.x && (player->pos.x + player->pos.w) <= (enemy.pos.x + enemy.pos.w))) {
		//Now we look at the y axis:
		if	((player->pos.y >= enemy.pos.y && player->pos.y <= (enemy.pos.y + enemy.pos.h)) ||
			((player->pos.y + player->pos.h) >= enemy.pos.y && (player->pos.y + player->pos.h) <= (enemy.pos.y + enemy.pos.h))) {
			//The sprites appear to overlap.
			return true;
		}
	}
	//The sprites do not overlap:
	return false;
}

bool Collider::Collision(Player* player, Enemy* enemy, int size) {
	for (int i = 0; i < size; ++i) {
		//If the leftmost or rightmost point of the first sprite lies somewhere inside the second, continue.
		if	((player->pos.x >= enemy->pos.x && player->pos.x <= (enemy->pos.x + enemy->pos.w)) ||
			((player->pos.x + player->pos.w) >= enemy->pos.x && (player->pos.x + player->pos.w) <= (enemy->pos.x + enemy->pos.w))) {
			//Now we look at the y axis:
			if	((player->pos.y >= enemy->pos.y && player->pos.y <= (enemy->pos.y + enemy->pos.h)) ||
				((player->pos.y + player->pos.h) >= enemy->pos.y && (player->pos.y + player->pos.h) <= (enemy->pos.y + enemy->pos.h))) {
				//The sprites appear to overlap.
				enemy->collided = true;
				return true;
			}
		}
	}
	//The sprites do not overlap:
	return false;
}
bool Collider::Collision(Bullet* b, Enemy* enemy, int size) {
	for (int i = 0; i < size; ++i) {
		//If the leftmost or rightmost point of the first sprite lies somewhere inside the second, continue.
		if ((b->pos.x >= enemy->pos.x && b->pos.x <= (enemy->pos.x + enemy->pos.w)) ||
			((b->pos.x + b->pos.w) >= enemy->pos.x && (b->pos.x + b->pos.w) <= (enemy->pos.x + enemy->pos.w))) {
			//Now we look at the y axis:
			if ((b->pos.y >= enemy->pos.y && b->pos.y <= (enemy->pos.y + enemy->pos.h)) ||
				((b->pos.y + b->pos.h) >= enemy->pos.y && (b->pos.y + b->pos.h) <= (enemy->pos.y + enemy->pos.h))) {
				//The sprites appear to overlap.
				enemy->collided = true;
				return true;
			}
		}
	}
	//The sprites do not overlap:
	return false;
}

bool Collider::Collision(Bullet* b, Player* p) {
		//If the leftmost or rightmost point of the first sprite lies somewhere inside the second, continue.
		if ((b->pos.x >=p->pos.x && b->pos.x <= (p->pos.x + p->pos.w)) ||
			((b->pos.x + b->pos.w) >= p->pos.x && (b->pos.x + b->pos.w) <= (p->pos.x + p->pos.w))) {
			//Now we look at the y axis:
			if ((b->pos.y >= p->pos.y && b->pos.y <= (p->pos.y +p->pos.h)) ||
				((b->pos.y + b->pos.h) >= p->pos.y && (b->pos.y + b->pos.h) <= (p->pos.y + p->pos.h))) {
				//The sprites appear to overlap.
				b->collided = true;
				return true;
			}
		}
	//The sprites do not overlap:
	return false;
}