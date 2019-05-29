#pragma once
#include "Enemy.h"

class Background
{
	struct BackgroundPos {
		float x, y;
	};

	
	float topSpawn = rand() % 900 + 780;
	float firstSpawn = rand() % 1280 + 1;
public:
	float landSpeed = 150;
	float cloudSpeed = 300;
	aie::Texture* texture;
	BackgroundPos pos{ firstSpawn, topSpawn };
	
	void Move(float deltaTime, float speed);
	
	
	Background();
	~Background();
};

