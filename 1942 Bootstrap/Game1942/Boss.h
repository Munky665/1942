#pragma once
#include <Texture.h>
#include <Renderer2D.h>

class Boss
{
protected:
	struct Position {
		float x, y;
	};

	aie::Texture* texture;
	aie::Renderer2D* renderer;
	Position pos;
	float speed = 100;
public:
	Boss(float x, float y);
	void FlyIn(float deltaTime);
	~Boss();
};

