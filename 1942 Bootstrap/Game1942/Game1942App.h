#pragma once
#include "SmallShip.h"
#include "Application.h"
#include "Background.h"
#include "Renderer2D.h"
#include "Collider.h"
#include <vector>

class Game1942App : public aie::Application {
public:
	static const int numOfBg = 4;
	Game1942App();
	virtual ~Game1942App();

	virtual bool startup();
	virtual void shutdown();
	void Create(Background Item[], int numOfBg);
	virtual void update(float deltaTime);
	virtual void draw();
	
protected:
	int screenWidth = 1280;
	int screenHeight = 720;
	int displacment = 100;
	Background* backgroundItems = new Background[numOfBg];
	Background* land = new Background[numOfBg];
	std::vector<Enemy*> smallShip ={
		new SmallShip,
		new SmallShip,
		new SmallShip,
		new SmallShip,
		new SmallShip};

	Collider* col;
	Player*	player;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};