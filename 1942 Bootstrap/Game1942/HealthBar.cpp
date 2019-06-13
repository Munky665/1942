#include "HealthBar.h"



HealthBar::HealthBar(float posX, float posY, float width, float height)
{
	m_posX = posX;
	m_posY = posY;
	m_width = width;
	m_height = height;

	m_currentValue = 100;
	m_maxValue = 100;

	isActive = true;
}


HealthBar::~HealthBar()
{
}

void HealthBar::Draw(aie::Renderer2D* renderer)
{
	renderer->setRenderColour(0, 0, 0, 1);
	renderer->drawBox(m_posX, m_posY, m_width, m_height, 0 , 0);
	
	float ratio = m_currentValue / m_maxValue;
	float full = m_width * ratio;
	float offsetX = m_posX - (m_width - full) * 0.5f;

	renderer->setRenderColour(1, 0, 0, 1);
	renderer->drawBox(offsetX, m_posY, full, m_height, 0, 0);
	
	renderer->setRenderColour(1, 1, 1, 1);
}
void HealthBar::SetValue(float value) {
	m_currentValue = value;
}

void HealthBar::Reset(float posX, float posY, float width, float height) {
	m_posX = posX;
	m_posY = posY;
	m_width = width;
	m_height = height;

	m_currentValue = 100;
	m_maxValue = 100;

	isActive = true;
}