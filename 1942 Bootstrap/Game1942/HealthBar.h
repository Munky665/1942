#pragma once
#include <Renderer2D.h>
class HealthBar
{
	float m_posX;
	float m_posY;
	float m_width;
	float m_height;

	float m_currentValue;
	float m_maxValue;
public:

	bool isActive = false;
	HealthBar(float posX, float posY, float width, float height);
	void SetValue(float value);
	void Draw(aie::Renderer2D* renderer);
	void Reset(float posX, float posY, float width, float height);
	~HealthBar();
};

