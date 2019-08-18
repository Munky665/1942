#pragma once
#include "Enemy.h"

class Background
{

	int topSpawn = rand() % 900 + 800;
	int firstSpawn = rand() % 1280 + 1;
public:
	bool Active = true;
	float landSpeed = 150;
	float cloudSpeed = 300;
	aie::Texture* texture;
	Vector3 pos = { firstSpawn, topSpawn,0 };
	Vector3 size = { 300, 300,0 };
	void Move(float deltaTime, float speed);
	void Reset();
	
	
	Background();
	~Background();
};

