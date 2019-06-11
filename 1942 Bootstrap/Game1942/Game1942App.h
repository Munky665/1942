#pragma once
#include <iostream>
#include "Application.h"
#include "Bullet.h"
#include "BigShip.h"
#include "SmallShip.h"
#include "Background.h"
#include "Renderer2D.h"
#include "Collider.h"
#include <vector>
#include <glfw3.h>
#include "MainMenu.h"
#include "PauseMenu.h"


class Game1942App : public aie::Application {
public:

	static const int numOfBg	 = 4;
	static const int numOfSShips = 10;
	static const int maxBullets  = 50;
	
	Game1942App();
	virtual ~Game1942App();
	virtual bool startup();
	virtual void shutdown();
	virtual void update(float deltaTime);
	virtual void draw();

	void CheckPVECollision(Player* p, Enemy* e, int s);
	void CheckBVECollision(std::vector<Bullet*> b, Enemy* e, int bs, int es);
	void CheckBVPCollision(std::vector<Bullet*> b, Player* p, int size);
	void Create(Background Item[], int numOfBg);

	int temp		 = 0;
	int screenWidth  = 1280;
	int screenHeight = 720;


protected:
	bool paused		= false;
	bool pauseL		= false;
	bool keyPressed = false;
	bool gameState  = false;
	bool menuState  = true;
	bool quitState  = false;
	int displacment = 100;

	Background* m_backgroundItems = new Background[numOfBg];
	Background* m_land			  = new Background[numOfBg];

	std::vector<Enemy*>  m_smallShip;
	std::vector<Bullet*> m_bullet;
	std::vector<Bullet*> m_eBullet;

	MainMenu*			m_menu;
	PauseMenu*			m_pauseMenu;
	Collider*			m_col;
	Player*				m_player;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};