#pragma once
#include "Enemy.h"

class Background
{
	struct BackgroundPos {
		float x, y;
		float w = 300, h = 300;
	};

	
	float topSpawn = rand() % 900 + 800;
	float firstSpawn = rand() % 1280 + 1;
public:
	bool Active = true;
	float landSpeed = 150;
	float cloudSpeed = 300;
	aie::Texture* texture;
	BackgroundPos pos{ firstSpawn, topSpawn };
	void Move(float deltaTime, float speed);
	void Reset();
	
	
	Background();
	~Background();
};

