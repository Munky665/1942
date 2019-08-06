#pragma once
#include "Enemy.h"

class Background
{

	float topSpawn = rand() % 900 + 800;
	float firstSpawn = rand() % 1280 + 1;
public:
	bool Active = true;
	float landSpeed = 150;
	float cloudSpeed = 300;
	aie::Texture* texture;
	vector2 pos = { firstSpawn, topSpawn };
	vector2 size = { 300, 300 };
	void Move(float deltaTime, float speed);
	void Reset();
	
	
	Background();
	~Background();
};

