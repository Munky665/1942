#pragma once
#include <iostream>
#include "Bullet.h"
#include "BigShip.h"
#include "SmallShip.h"
#include "Application.h"
#include "Background.h"
#include "Renderer2D.h"
#include "Collider.h"
#include <vector>
#include <glfw3.h>


class Game1942App : public aie::Application {
public:
	static const int numOfBg = 4;
	static const int numOfSShips = 5;
	static const int maxBullets = 50;
	Game1942App();
	virtual ~Game1942App();

	virtual bool startup();
	virtual void shutdown();
	void Create(Background Item[], int numOfBg);
	virtual void update(float deltaTime);
	virtual void draw();
	virtual void Pause(aie::Input* input);
	void CheckPVECollision(Player* p, Enemy* e, int s);
	void CheckBVECollision(std::vector<Bullet*> b, Enemy* e, int bs, int es);
	void CheckBVPCollision(std::vector<Bullet*> b, Player* p, int size);
	int temp = 0;
	int screenWidth = 1280;
	int screenHeight = 720;
	
protected:
	bool paused = false;
	bool keyPressed = false;
	int displacment = 100;
	Background* backgroundItems = new Background[numOfBg];
	Background* land = new Background[numOfBg];
	
	std::vector<Enemy*> smallShip;
	std::vector<Bullet*> bullet;
	std::vector<Bullet*> eBullet;

	Collider* col;
	Player*	player;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};