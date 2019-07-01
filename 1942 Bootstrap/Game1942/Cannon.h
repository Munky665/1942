#pragma once
#include "Boss.h"
#include "Collider.h"

class Cannon :
	public Boss
{
protected:


	vector3 stoppingPointTwo = { 0,295,0 };
	vector3 cannonOne = { 390,1200,0 };
	vector3 cannonTwo = { 172,1100,0 };
	vector3 cannonThree = { 890,1200,0 };
	vector3 cannonFour = { 1108,1100,0 };

	vector3 rightscreenC{ 1272,0,0 };
	vector3 rightscreenC2{ 1490,0,0 };
	vector3 leftscreenC{ -48,0,0 };
	vector3 leftscreenC2{ -266,0,0 };

	bool isActive = false;
	float firstOffSetX = 250;
	float secondOffSetX = 475;
	float yOffSet = 105;
	float rotate = 5;
	float value = 2;
	int maxBullets = 50;
	bool isAlive = true;
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

	int health = 50;
	aie::Texture* destroyed;
	std::vector<Bullet*> bullets;
	Collider* col;

public:
	Cannon(int i);
	void Move(float deltaTime, Player* p, std::vector<Bullet*> pB);
	void Reset(int i) override;
	void Draw() override;
	vector3 cannonPosition = { 0,0,0 };
	float height = 54;
	float width = 57;
	~Cannon();
};

