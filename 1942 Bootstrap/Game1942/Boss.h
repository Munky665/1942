#pragma once
#include <Texture.h>
#include <Renderer2D.h>
#include "Vector2.h"
#include "DynamicArray.h"
#include "Bullet.h"
#include <time.h>

class Boss
{
protected:
	struct position {
		float x, y;
		float h = 600;
		float w = 1280;
	};

	float m_speed = 100;
	float m_startingY = 1200;
	float m_xPosition = 1280 / 2;
	float stopPosition = 400;
	float stopPositionTwo = 295;
	bool outsideCannon = false;
	bool inPosition = false;
	bool left = false;
	bool right = false;
	float screenLeft = 200;
	float screenRight = 1180;


	vector2 pos = { m_xPosition, m_startingY };
	vector2 stoppingPointOne = { 0,400 };
	vector2 rightscreen{ 1020,0 };
	vector2 leftscreen{ 200,0 };
	aie::Renderer2D*	m_renderer;
	aie::Texture*		m_texture;
public:
	Boss();
	virtual void Move(float deltaTime);
	virtual void Draw(aie::Renderer2D* renderer);
	virtual void Reset(int i);
	~Boss();
	float magOne;
};

