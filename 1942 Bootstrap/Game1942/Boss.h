#pragma once
#include <Texture.h>
#include <Renderer2D.h>
#include "DynamicArray.h"
#include "Bullet.h"
#include <time.h>
#include <MathLib.h>
#include <assert.h>
#include <vector>

class Boss
{
protected:
	struct position {
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
	float screenRight = 1000;
	

	
	Vector3 stoppingPointOne = { m_xPosition,400,1 };
	Vector3 rightscreen = { 1020,0,0 };
	Vector3 leftscreen = { 200,0,0 };
	Vector3 movement = { 200,0,0 };
	Vector3 moveDown = { 0,200,0 };
	aie::Renderer2D*	m_renderer;
	aie::Texture*		m_texture;

	
	Boss* parent = nullptr;
	std::vector<Boss*> children;

public:
	Boss();
	virtual void Move(float deltaTime);
	virtual void Draw(aie::Renderer2D* renderer);
	virtual void Reset(int i);
	void updateTransform();
	void translate(float x, float y);
	void addChild(Boss* child);

	~Boss();
	float magOne;
	Matrix3 globalTransform = Matrix3::identity;
	Matrix3 localTransform = Matrix3::identity;
};

