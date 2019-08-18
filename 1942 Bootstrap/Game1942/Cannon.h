#pragma once
#include "Boss.h"
#include "Collider.h"

class Cannon :
	public Boss
{
protected:


	Vector3 stoppingPointTwo = { 0,295,0 };
	Vector3 cannonOne = { 390,1200,  1 };
	Vector3 cannonTwo = { 172,1100  ,1 };
	Vector3 cannonThree = { 890,1200,1 };
	Vector3 cannonFour = { 1108,1100,1}; //bottom right

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
	int score = 500;
	int maxHealth = 30;
	int health = maxHealth;
	aie::Texture* destroyed;
	DynamicArray<Bullet*> bullets;
	Collider* coll;
	
	void CannonFired(float deltaTime, Player* p, DynamicArray<Bullet*> pB);

public:
	bool sound = false;
	Cannon(int i);
	void Fire(float deltaTime, Player* p, DynamicArray<Bullet*> pB);
	bool hasFiredTimer();
	void Reset(int i) override;
	void Draw(aie::Renderer2D* m_renderer) override;
	bool toggled = false;
	bool isAlive = true;
	float height = 54;
	float width = 57;
	~Cannon();
};

