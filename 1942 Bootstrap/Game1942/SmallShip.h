#pragma once
#include "Enemy.h"

class SmallShip : public Enemy
{
	int temp = 0;
	float respwan = rand() % 1280 + 1;
public:
	SmallShip();
	void Move(float deltaTime) override;
	void textureEnemy() override;
	void Size() override;
	~SmallShip();
};

