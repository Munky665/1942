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
#include <SFML/Audio.hpp>
#include <queue>




class Game1942App : public aie::Application {
public:

	const int numOfBg		= 4;
	const int numOfSShips	= 10;
	const int maxBullets	= 100;

	
	Game1942App();
	virtual ~Game1942App();
	virtual bool startup();
	virtual void shutdown();
	virtual void update(float deltaTime);
	virtual void draw();
	void FirstBoot();
	void ResetItems();
	void DeActivate();
	void BossAndEnemyTimer();
	void ResetShips();
	void MoveBoss(float deltaTime);
	void MovePlayerFiredBullets(float deltaTime);
	void MoveEnemyFiredBullets(float deltaTime);
	void MoveBackground(float deltaTime);
	void MoveEnemyAndCheckFire(float deltaTime);
	void CheckPlayerCollision();
	void CheckEnemyCollision(int i);
	void SpawnHealth(int i);
	void PickUpHealth(float deltaTime);
	void LoadSounds();
	void BossState();
	void DeathState();
	void PausedState();

	void DrawDeathMenu(aie::Renderer2D* renderer);
	void DrawBoss(aie::Renderer2D* renderer);
	void DrawBullets(aie::Renderer2D* renderer);
	void DrawEnemyShips(aie::Renderer2D* renderer);
	void DrawBackground(aie::Renderer2D* renderer);

	void DeleteFromMemory();

	int temp		 = 0;
	int screenWidth  = 1280;
	int screenHeight = 720;


protected:
	float numberOfSounds = 4;
	float shootVol = 40;
	float explosionVol = 50;
	float hitvol = 50;
	float musicVol = 50;

	int size;
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
	int startTimer  = 2;
	int bossTimer = 180;
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

	sf::Music*						 music;
	std::vector<sf::SoundBuffer>     buffer;
	std::vector<sf::Sound>			 sound;

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