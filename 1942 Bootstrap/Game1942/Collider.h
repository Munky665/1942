#pragma once
#include "Background.h"
class Collider
{
public:
	bool Collision(Background sprite_1, Background sprite_2);
	bool Collision(Player* sprite_1, Enemy* sprite_2);
	bool Collision(Player* sprite_1, std::vector<Enemy*> sprite_2);
	Collider();
	~Collider();
};

