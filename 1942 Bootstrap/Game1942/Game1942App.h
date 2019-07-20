#pragma once
#include <iostream>
#include "Application.h"
#include "Bullet.h"
#include "BigShip.h"
#include "SmallShip.h"
#include "Background.h"
#include "Renderer2D.h"
#include "Collider.h"
#include "DynamicArray.h"
#include <glfw3.h>
#include "MainMenu.h"
#include "PauseMenu.h"
#include "HealthBar.h"
#include "Clouds.h"
#include "Land.h"
#include "GameOver.h"
#include "HealthPickUp.h"
#include "Cannon.h"


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
	void DeActivate();


	int temp		 = 0;
	int screenWidth  = 1280;
	int screenHeight = 720;


protected:
	
	bool isDead		= false;
	bool firstpass	= true;
	bool con		= false;
	bool paused		= false;
	bool pauseL		= false;
	bool keyPressed = false;
	bool gameState  = false;
	bool menuState  = true;
	bool quitState  = false;
	bool deathState = false;
	bool enemyState = false;
	bool bossActive = false;
	int startTimer = 5;
	int bossTimer	= 120;
	int displacment = 100;
	int m_duration	= 2;
	int m_waitTime	= 2;
	int cannonDestroyed = 0;
	clock_t start = clock();
	clock_t wait = clock();
	float duration;

	DynamicArray<Background*> m_clouds;
	DynamicArray<Background*> m_land;

	DynamicArray<Enemy*>  m_smallShip;
	DynamicArray<Bullet*> m_bullet;
	DynamicArray<Bullet*> m_eBullet;
	DynamicArray<Cannon*> m_turrets;

	Boss*				m_boss;
	HealthBar*			m_bar;
	MainMenu*			m_menu;
	PauseMenu*			m_pauseMenu;
	HealthPickUp*		m_healthPickUp;
	Collider*			m_col;
	Player*				m_player;
	GameOver*			m_death;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};