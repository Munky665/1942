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

bool Collider::Collision(Player* player, Enemy* enemy) {
	//If the leftmost or rightmost point of the first sprite lies somewhere inside the second, continue.
	if ((player->pos.x >= enemy->pos.x && player->pos.x <= (enemy->pos.x + enemy->pos.w)) ||
		((player->pos.x + player->pos.w) >= enemy->pos.x && (player->pos.x + player->pos.w) <= (enemy->pos.x + enemy->pos.w))) {
		//Now we look at the y axis:
		if ((player->pos.y >= enemy->pos.y && player->pos.y <= (enemy->pos.y + enemy->pos.h)) ||
			((player->pos.y + player->pos.h) >= enemy->pos.y && (player->pos.y + player->pos.h) <= (enemy->pos.y + enemy->pos.h))) {
			//The sprites appear to overlap.
			return true;
		}
	}
	//The sprites do not overlap:
	return false;
}

bool Collider::Collision(Player* player, std::vector<Enemy*> enemy) {
	for (int i = 0; i < enemy.size(); ++i) {
		//If the leftmost or rightmost point of the first sprite lies somewhere inside the second, continue.
		if ((player->pos.x >= enemy[i]->pos.x && player->pos.x <= (enemy[i]->pos.x + enemy[i]->pos.w)) ||
			((player->pos.x + player->pos.w) >= enemy[i]->pos.x && (player->pos.x + player->pos.w) <= (enemy[i]->pos.x + enemy[i]->pos.w))) {
			//Now we look at the y axis:
			if ((player->pos.y >= enemy[i]->pos.y && player->pos.y <= (enemy[i]->pos.y + enemy[i]->pos.h)) ||
				((player->pos.y + player->pos.h) >= enemy[i]->pos.y && (player->pos.y + player->pos.h) <= (enemy[i]->pos.y + enemy[i]->pos.h))) {
				//The sprites appear to overlap.
				enemy[i]->collided = true;
				//player.lives -= 1;
				return true;
			}
		}
	}
	//The sprites do not overlap:
	return false;
}