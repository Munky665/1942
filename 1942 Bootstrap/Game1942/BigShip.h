#pragma once
#include "Enemy.h"
class BigShip :
	public Enemy
{
private:
	int temp			  = 0;
	int respwan		  = rand() % 1280 + 1;
	float BigPlaneBooster = 20;
public:


	BigShip();
	void Move(float deltaTime, int sW, int sH) override;
	void textureEnemy() override;
	void Size() override;
	void Reset(int sW, int sH) override;
	~BigShip();
};

