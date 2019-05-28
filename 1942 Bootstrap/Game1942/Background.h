#pragma once
#include "Player.h"
#include <time.h>
#include <random>

class Background
{
	struct BackgroundPos {
		float x, y;
	};

	float speed = 500;
	float topSpawn = 740;

public:
	aie::Texture* texture;
	BackgroundPos pos{ 0, topSpawn };
	
	void Move(float deltaTime);
	
	
	Background();
	~Background();
};

