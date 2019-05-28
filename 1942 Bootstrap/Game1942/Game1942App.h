#pragma once
#include "Application.h"
#include "Background.h"
#include "Renderer2D.h"
#include <vector>

class Game1942App : public aie::Application {
public:
	static const int numOfBg = 4;
	Game1942App();
	virtual ~Game1942App();

	virtual bool startup();
	virtual void shutdown();
	void Create(Background* Item[], int numOfBg);
	virtual void update(float deltaTime);
	virtual void draw();
	Background* backgroundItems[numOfBg];
protected:
	
	
	Player*	player;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};