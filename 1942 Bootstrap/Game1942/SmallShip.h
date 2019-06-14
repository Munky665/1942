#pragma once
#include "Enemy.h"

class SmallShip : public Enemy
{
private:
	int temp	  = 0;
	int respwan = rand() % 1280 + 1;
public:
	SmallShip();
	void Move(float deltaTime, int sW, int sH) override;
	void textureEnemy() override;
	void Size() override;
	void Reset(int sW, int sH) override;
	~SmallShip();
};

