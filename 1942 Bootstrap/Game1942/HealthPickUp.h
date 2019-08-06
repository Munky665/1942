#pragma once
#include <Texture.h>
#include <Renderer2D.h>
#include <random>
#include "Vector2.h"

class HealthPickUp
{
protected:

	aie::Texture* texture;
	aie::Renderer2D* renderer;
	bool exists = false;
	float travelSpeed = 150;
	const int variance = 25;
	float temp;


public:

	vector2 pos;
	vector2 size = { 64, 64 };

	HealthPickUp();
	void Move(float deltaTime);
	void SpawnHealth(float x, float y);
	void DeActivate();
	void Draw(aie::Renderer2D* renderer);
	~HealthPickUp();
};

