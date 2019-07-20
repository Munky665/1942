#pragma once
#include "Boss.h"
#include "Collider.h"

class Cannon :
	public Boss
{
protected:


	vector2 stoppingPointTwo = { 0,295 };
	vector2 cannonOne = { 390,1200 };
	vector2 cannonTwo = { 172,1100 };
	vector2 cannonThree = { 890,1200 };
	vector2 cannonFour = { 1108,1100 }; //bottom right

	vector2 rightscreenC{ 1272,0 };
	vector2 rightscreenC2{ 1490,0 };
	vector2 leftscreenC{ -48,0 };
	vector2 leftscreenC2{ -266,0 };

	bool isActive = false;
	float firstOffSetX = 250;
	float secondOffSetX = 475;
	float yOffSet = 105;
	float rotate = 5;
	float value = 2;
	int maxBullets = 50;

	int positionN = 1;
	clock_t start = clock();
	clock_t wait = clock();
	float fireWait = 0.25;
	float duration;
	bool hasFired = false;
	float velocity = 400;

	bool can1 = false,
		 can2 = false,
		 can3 = false,
		 can4 = false;
	int score = 100;
	int health = 50;
	aie::Texture* destroyed;
	DynamicArray<Bullet*> bullets;
	Collider* col;

public:
	Cannon(int i);
	void Move(float deltaTime, Player* p, DynamicArray<Bullet*> pB);
	void Reset(int i) override;
	void Draw() override;
	bool toggled = false;
	bool isAlive = true;
	vector2 cannonPosition = { 0,0 };
	float height = 54;
	float width = 57;
	~Cannon();
};

