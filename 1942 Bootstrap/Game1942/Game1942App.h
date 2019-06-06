#pragma once
#include "Bullet.h"
#include "BigShip.h"
#include "SmallShip.h"
#include "Application.h"
#include "Background.h"
#include "Renderer2D.h"
#include "Collider.h"
#include <vector>

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
	void CheckCollision(Player* p, std::vector<Enemy*> e, int s);
	void CheckCollision(std::vector<Bullet*> b, std::vector<Enemy*> e, int bs, int es);
	void CheckCollision(std::vector<Bullet*> b, Player* p);
	int temp = 0;
	

protected:
	bool paused = false;
	int screenWidth = 1280;
	int screenHeight = 720;
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