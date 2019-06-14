#pragma once
#include <Texture.h>
#include <Renderer2D.h>
#include <random>

class HealthPickUp
{
protected:
	struct Position {
		float x, y;
		float w = 64, 
			  h = 64;
	};

	aie::Texture* texture;
	aie::Renderer2D* renderer;
	bool exists = false;
	float travelSpeed = 150;
	float temp;


public:

	Position pos;

	HealthPickUp();
	void Move(float deltaTime);
	void SpawnHealth(float x, float y);
	void DeActivate();
	void Draw();
	~HealthPickUp();
};

