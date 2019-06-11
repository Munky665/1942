#include "Game1942App.h"

Game1942App::Game1942App() {

}

Game1942App::~Game1942App() {

}


//creates clouds and land
void Game1942App::Create(Background Item[], int num) {
	for (int i = 0; i < num; ++i) {
		if(num == numOfBg)
		Item[i].texture = new aie::Texture("./textures/Cloud.png");
	}
}
//checks player vs enemy collisions
void Game1942App::CheckPVECollision(Player* p, Enemy* e, int s) {
	for (int i = 0; i < s; ++i) {
		if (m_col->Collision(p, e, s) == true && p->immune == false) {
			p->immune = true;
			p->health -= e->crashDamage;
			p->score = p->score + e->scoreValue;
			e->isAlive = false;
			std::cout << "Player Collided with ship" << std::endl;
		}
	}
}
//checks player bullet vs enemy collisions
void Game1942App::CheckBVECollision(std::vector<Bullet*> b, Enemy* e, int bs, int es) {
	for (int j = 0; j < bs; j++) {
		if (m_col->Collision(b[j], e, bs) == true) {
			if (e->collided == true) {
				m_player->score = m_player->score + e->scoreValue;
				e->isAlive = false;
				b[j]->collided = true;
				std::cout << "Player Bullet " << b[j] << " Collided with " << e << std::endl;
			}
		}
	}
}
//checks enemy bullet vs player collisions 
void Game1942App::CheckBVPCollision(std::vector<Bullet*> b, Player* p, int size) {
	for (int i = 0; i < size; ++i) {
		if (m_col->Collision(b[i], p) == true && p->immune == false) {
			p->health -= b[i]->damage;
			b[i]->collided = true;
			p->immune = true;
			std::cout << "Bullet Collided with Player" << std::endl;
		}
	}
}


bool Game1942App::startup() {
	
	if (menuState == true) {
		//build menu
		setBackgroundColour(0, 0, 0, 0);
		m_menu = new MainMenu();
		m_menu->startup();
		return true;
	}
	
	else if (gameState == true) {

		//set background colour
		setBackgroundColour(0, 0.51, 2.55, 0.9);
		//create renderer
		m_2dRenderer = new aie::Renderer2D();
		//create player
		m_player = new Player();
		std::cout << "loaded Player" << std::endl;
		//create font
		m_font = new aie::Font("./font/consolas.ttf", 32);
		//allocate pngs to land in background
		for (int i = 0; i < numOfBg; ++i) {
			m_land[i].texture = new aie::Texture("./textures/land.png");
		}
		std::cout << "Loaded land" << std::endl;
		//create bullets
		for (int i = 0; i < maxBullets; ++i) {
			m_bullet.push_back(new Bullet());
			m_eBullet.push_back(new Bullet());
		}
		std::cout << "loaded Bullets " << std::endl;
		//creates clouds
		Create(m_backgroundItems, numOfBg);
		std::cout << "Loaded Clouds" << std::endl;
		//Create Enemies
		for (int i = 0; i < numOfSShips; ++i) {
			temp = rand() % 2 + 1;
			switch (temp) {
			case 1:
				m_smallShip.push_back(new SmallShip());
				break;
			case 2:
				m_smallShip.push_back(new BigShip());
			};
			std::cout << "Loaded Ships" << std::endl;
		}
		return true;
	}
}

void Game1942App::shutdown() {
	

	if (gameState == true  &&
		paused	  == false &&
		menuState == false   )
	{
			m_pauseMenu->ShutDown();
			delete m_pauseMenu;

	}
	if (menuState == true)
	{
		m_menu->shutdown();
		delete m_menu;
	}
	else if (gameState == true) 
	{
		delete[] m_backgroundItems;
		delete[] m_land;
		delete m_font;
		delete m_2dRenderer;
		std::cout << "game State deleted" << std::endl;
	}

}

void Game1942App::update(float deltaTime) 
{

	if (menuState == true) {
		m_menu->Menu(gameState, quitState);
		if (gameState == true) 
		{
			shutdown();
			menuState = false;
			startup();
		}
		else if (quitState == true) 
		{
			quit();
		}

	}

	// input example
	aie::Input* input = aie::Input::getInstance();
	if (gameState == true && paused == false) 
	{

		int reverse = numOfSShips - 1;

		for (int i = 0; i < numOfSShips; ++i) 
		{
			if (m_smallShip[i]->isAlive == false) 
			{
				m_smallShip[i]->Reset(screenWidth, screenHeight);
			}
		}

		//player fire Bullet
		if (input->wasKeyPressed(aie::INPUT_KEY_SPACE)) {
			for (int i = 0; i < maxBullets; ++i) {
				if (m_bullet[i]->exists != true && m_player->playerFired != true) 
				{
					m_bullet[i]->PlayerFired(m_player);
					std::cout << "bullet fired" << std::endl;
				}
			}
		}

		m_player->playerFired = false;
		//move each bullet that has been fired
		for (int i = 0; i < maxBullets; ++i) 
		{
			if (m_bullet[i]->exists != false) 
			{

				m_bullet[i]->Move(deltaTime);

				if (m_bullet[i]->pos.y > screenHeight) 
				{
					m_bullet[i]->exists = false;
				}
				else if (m_bullet[i]->collided == true) 
				{
					m_bullet[i]->exists = false;
					m_bullet[i]->collided = false;
				}
			}
			else if (m_bullet[i]->exists != true) 
			{
				m_bullet[i]->pos.x = m_player->pos.x;
				m_bullet[i]->pos.y = m_player->pos.y;
			}
		}

		//move background items
		for (int i = 0; i < numOfBg; ++i) 
		{
			m_backgroundItems[i].Move(deltaTime, m_backgroundItems[i].cloudSpeed);
			m_land[i].Move(deltaTime, m_land[i].landSpeed);

			for (int j = i + 1; j < numOfBg; ++j) 
			{
				if (m_col->Collision(m_land[i], m_land[j]) == true) 
				{
					m_land[j].pos.x = rand() % screenWidth + 1;
					m_land[j].pos.y += displacment;
				}

				if (m_col->Collision(m_backgroundItems[i], m_backgroundItems[j]) == true) 
				{
					m_backgroundItems[j].pos.x = rand() % screenWidth + 1;
					m_backgroundItems[j].pos.y += displacment;
				}
			}
		}
		//move the player
		m_player->Move(input, deltaTime);
		m_player->Contain(screenWidth, screenHeight);
		//move Enemy
		for (int i = 0; i < numOfSShips; ++i)
		{
			if (m_smallShip[i]->isAlive == true && m_smallShip[i]->hasStopped != true)
			{
				if (m_smallShip[i]->pos.y < screenHeight * 0.5)
				{
					m_smallShip[i]->PauseFlight();
				}
				else
					m_smallShip[i]->Move(deltaTime, screenWidth, screenHeight);
			}
			else if (m_smallShip[i]->isAlive == true && m_smallShip[i]->hasStopped == true)
			{
				m_smallShip[i]->Move(deltaTime, screenWidth, screenHeight);
			}

			for (int b = 0; b < maxBullets; ++b) 
			{
				for (int i = 0; i < numOfSShips; ++i)
				{
					if (m_eBullet[b]->exists != true)
					{
						if (m_smallShip[i]->hasFired != true)
						{
							m_eBullet[b]->EnemyFired(m_smallShip[i]);
						}
					}
				}
			}
		}
		for (int b = 0; b < maxBullets; ++b)
		{
			//move each bullet that has been fired
			if (m_eBullet[b]->exists != false)
			{

				m_eBullet[b]->Move(deltaTime);

				if (m_eBullet[b]->pos.y <= 0)
				{
					m_eBullet[b]->exists = false;
					m_eBullet[b]->efire = false;
					std::cout << "bullet removed" << std::endl;
					if (b < numOfSShips && m_eBullet[b]->exists == false) 
					{
						m_smallShip[b]->hasFired = false;
					}
				}
				else if (m_eBullet[b]->collided != false)
				{
					m_eBullet[b]->efire = false;
					m_eBullet[b]->exists = false;
					std::cout << "bullet removed" << std::endl;
					if (b < numOfSShips && m_eBullet[b]->exists == false) 
					{
						m_smallShip[b]->hasFired = false;
					}
				}
			}

		}

		//check if player collided with enemy
		if (m_player->immune == false) 
		{
			for (int i = 0; i < numOfSShips; ++i) 
			{
				CheckPVECollision(m_player, m_smallShip[i], numOfSShips);
			}
			//check for player bullet collisions
			for (int i = 0; i < numOfSShips; ++i) 
			{
				CheckBVECollision(m_bullet, m_smallShip[i], maxBullets, numOfSShips);
			}
		}
		//check for enemy bullet collisions
		for (int i = 0; i < numOfSShips; ++i) 
		{
			CheckBVPCollision(m_eBullet, m_player, maxBullets);


		}
		//cese imunity after collision check
		m_player->immune = false;

		//health check
		if (m_player->health <= 0)
		{
			m_player->lives -= 1;
			m_player->health = m_player->maxHealth;
		}

		// exit the application
		if (m_player->lives < 0)
		{
			shutdown();
			gameState = false;
			menuState = true;
			startup();

		}
		if (input->isKeyDown(aie::INPUT_KEY_ESCAPE)) {
			paused = true;
		}


		//check screen size
		auto window = glfwGetCurrentContext();
		glfwGetWindowSize(window, &screenWidth, &screenHeight);
	}
	if (paused == true)
	{
		if (pauseL == false)
		{
			m_pauseMenu = new PauseMenu();
			m_pauseMenu->StartUp();
			pauseL = true;
		}
		else if(pauseL == true)
		{
			m_pauseMenu->Pause(paused, quitState);
		}
		if (paused == false && quitState != true) 
		{
			shutdown();
			pauseL = false;

		}
		else if (quitState == true) 
		{
			shutdown();
			gameState = false;
			menuState = true;
			startup();
			quitState = false;
			pauseL	  = false;
		}
		
	}
}

void Game1942App::draw() {
	clearScreen();
	if (menuState == true) {
		m_menu->draw();
	}
	else if (gameState == true) {
		if (paused == true)
		{
			m_pauseMenu->Draw(screenWidth, screenHeight);
		}
		// wipe the screen to the background colour
		// begin drawing sprites
		m_2dRenderer->begin();

		// draw your stuff here!

		//draw bullet
		for (int i = 0; i < maxBullets; ++i)
		{
			if (m_bullet[i]->exists != false)
			{
				m_2dRenderer->drawSprite(m_bullet[i]->texture,
					m_bullet[i]->pos.x,
					m_bullet[i]->pos.y,
					m_bullet[i]->pos.w,
					m_bullet[i]->pos.h);
			}
		}
		for (int j = 0; j < maxBullets; ++j)
		{
			if (m_eBullet[j]->exists != false)
			{
				m_2dRenderer->drawSprite(m_eBullet[j]->texture,
					m_eBullet[j]->pos.x,
					m_eBullet[j]->pos.y,
					m_eBullet[j]->pos.w,
					m_eBullet[j]->pos.h);
			}
		}
		//draw lives
		m_player->RenderLives(m_2dRenderer, m_font, screenHeight);
		m_player->RenderScore(m_2dRenderer, m_font, screenWidth, screenHeight);
		m_player->RenderHealth(m_2dRenderer);

		//Draw Enemy 
		for (int i = 0; i < numOfSShips; ++i)
		{
			if (m_smallShip[i]->isAlive == true)
			{
				m_2dRenderer->drawSprite(m_smallShip[i]->texture,
					m_smallShip[i]->pos.x,
					m_smallShip[i]->pos.y,
					m_smallShip[i]->pos.w,
					m_smallShip[i]->pos.h, 0, 0);
			}
		}

		for (int i = 0; i < numOfBg; ++i)
		{
			//draw clouds	
			m_2dRenderer->drawSprite(m_backgroundItems[i].texture,
				m_backgroundItems[i].pos.x,
				m_backgroundItems[i].pos.y, 300, 300, 0, 99);
			//draw land
			m_2dRenderer->drawSprite(m_land[i].texture,
				m_land[i].pos.x,
				m_land[i].pos.y, 300, 300, 0, 100);
		}
		//draw player
		m_2dRenderer->drawSprite(m_player->playerTexture,
			m_player->pos.x,
			m_player->pos.y,
			m_player->pos.w + 30,
			m_player->pos.h + 30, 0, 1);
		// output some text, uses the last used colour
		m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

		// done drawing sprites
		m_2dRenderer->end();


	}
}
