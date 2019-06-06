#pragma once
#include "Enemy.h"
class BigShip :
	public Enemy
{
private:
	int temp = 0;
	float respwan = rand() % 1280 + 1;
	float BigPlaneBooster = 20;
public:
	BigShip();
	void Move(float deltaTime) override;
	void textureEnemy() override;
	void Size() override;
	~BigShip();
};

