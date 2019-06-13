#include "Game1942App.h"

Game1942App::Game1942App() {

}

Game1942App::~Game1942App() {

}


bool Game1942App::startup() 
{
	
	if (menuState == true) 
	{
		//build menu
		setBackgroundColour(0, 0, 0, 0);
		m_menu = new MainMenu();
		m_menu->startup();
		return true;
	}
	
	else if (gameState == true)
	{
		if (firstpass == true) {
			m_bar = new HealthBar(screenWidth * 0.5f, screenHeight - 20, 400, 20);
			//create player
			m_player = new Player();
			//create renderer
			m_2dRenderer = new aie::Renderer2D();
			//create font
			m_font = new aie::Font("./font/consolas.ttf", 32);
			//set background colour
			setBackgroundColour(0, 0.51, 2.55, 0.9);
			//creates clouds
			//allocate pngs to land in background
			for (int i = 0; i < numOfBg; ++i)
			{
				m_land.push_back(new Land());
				m_clouds.push_back(new Clouds());
			}
			//create bullets
			for (int i = 0; i < maxBullets; ++i)
			{
				m_bullet.push_back(new Bullet());
				m_eBullet.push_back(new Bullet());
			}
			//Create Enemies
			for (int i = 0; i < numOfSShips; ++i)
			{
				temp = rand() % 2 + 1;
				switch (temp)
				{
				case 1:
					m_smallShip.push_back(new SmallShip());
					break;
				case 2:
					m_smallShip.push_back(new BigShip());
				};
			}
			firstpass = false;
		}
		else {
			for (int i = 0; i < numOfBg; ++i)
			{
				m_land[i]->Reset();
				m_clouds[i]->Reset();
			}
			//create bullets
			for (int i = 0; i < maxBullets; ++i)
			{
				m_bullet[i]->Reset();
				m_eBullet[i]->Reset();
			}
			//Create Enemies
			for (int i = 0; i < numOfSShips; ++i)
			{
				m_smallShip[i]->Reset(screenWidth, screenHeight);
			}
			setBackgroundColour(0, 0.51, 2.55, 0.9);
			m_player->Reset();
			m_bar->Reset(screenWidth * 0.5f, screenHeight - 20, 400, 20);
		}
			return true;
	}
}

void Game1942App::shutdown() 
{
	//checks if pause menu is active
	if (pauseL == true  &&
		paused == false  )
	{
			m_pauseMenu->ShutDown();
			delete m_pauseMenu;
			std::cout << "Closed  paused Menu" << std::endl;

	}
	//deletes main menu from memory
	if (menuState == true)
	{
		m_menu->shutdown();
		delete m_menu;
	}
	//checks if game state is active
	if (gameState ==  true && pauseL == true && con != true) 
	{
		if (m_gameOver == true) {
			m_bullet.~vector();
			m_eBullet.~vector();
			m_smallShip.~vector();
			delete m_bar;
			m_clouds.~vector();
			m_land.~vector();
			delete m_player;
			delete m_font;
			delete m_2dRenderer;
		}
		else if (menuState == false) {
			for (int i = 0; i < numOfBg; ++i)
			{
				m_land[i]->Active = false;
				m_clouds[i]->Active = false;
			}
			//create bullets
			for (int i = 0; i < maxBullets; ++i)
			{
				m_bullet[i]->exists = false;
				m_eBullet[i]->exists = false;
			}
			//Create Enemies
			for (int i = 0; i < numOfSShips; ++i)
			{
				m_smallShip[i]->isAlive = false;
			}
			m_bar->isActive = false;

		}
	}
	con = false;

}

void Game1942App::update(float deltaTime) 
{
	//checks if main menu is active
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
		m_bar->SetValue(m_player->health);
		m_player->immune = false;
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
				}
			}
		}

		m_player->playerFired = false;
		//move each bullet that has been fired
		for (int i = 0; i < maxBullets; ++i) 
		{
			if (m_bullet[i]->exists		 != false) 
			{

				m_bullet[i]->Move(deltaTime);
				//remove bullet if it leaves screen
				if (m_bullet[i]->pos.y > screenHeight) 
				{
					m_bullet[i]->exists   = false;
				}
				//remove bullet if it has collided
				else if (m_bullet[i]->collided == true) 
				{
					m_bullet[i]->exists   = false;
					m_bullet[i]->collided = false;
				}
			}
			//move bullets back to player position while non-existant
			else if (m_bullet[i]->exists != true) 
			{
				m_bullet[i]->pos.x = m_player->pos.x;
				m_bullet[i]->pos.y = m_player->pos.y;
			}
		}

		//move background items
		for (int i = 0; i < numOfBg; ++i) 
		{
			m_clouds[i]->Move(deltaTime, m_clouds[i]->cloudSpeed);
			m_land[i]->Move(deltaTime, m_land[i]->landSpeed);

			for (int j = i + 1; j < numOfBg; ++j) 
			{
				//check if land collides with one another
				if (m_col->Collision(m_land[i], m_land[j]) == true) 
				{
					m_land[j]->pos.x = rand() % screenWidth + 1;
					m_land[j]->pos.y += displacment;
				}
				//check if clouds collide with one another
				if (m_col->Collision(m_clouds[i], m_clouds[j]) == true) 
				{
					m_clouds[j]->pos.x = rand() % screenWidth + 1;
					m_clouds[j]->pos.y += displacment;
				}
			}
		}
		//move the player
		m_player->Move(input, deltaTime);
		m_player->Contain(screenWidth, screenHeight);
		//move Enemy
		for (int i = 0; i < numOfSShips; ++i)
		{
			//pause ship flight and move
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
			//check if enemy has fired bullet
			for (int b = 0; b < maxBullets; ++b) 
			{
				for (int j = 0; j < numOfSShips; ++j)
				{
					m_smallShip[j]->WaitToFire();
					if (m_eBullet[b]->exists != true && m_smallShip[j]->hasFired != true)
					{
						m_eBullet[b]->EnemyFired(m_smallShip[j]);
						m_smallShip[j]->hasFired = true;
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
				//if bullet passes out of bottom of screen remove
				if (m_eBullet[b]->pos.y <= 0)
				{
					m_eBullet[b]->collided = false;
					m_eBullet[b]->exists = false;
					m_eBullet[b]->efire  = false;
				}
			}

		}

		//check collisions if player is not immune
		if (m_player->immune == false)
		{
			for (int i = 0; i < numOfSShips; ++i)
			{
				//check if player collided with enemy
				m_col->CheckPVECollision(m_player, m_smallShip[i], numOfSShips);
			}
			//check for bullet vs enemy collisions
			for (int i = 0; i < numOfSShips; ++i)
			{
				m_col->CheckBVECollision(m_bullet, m_smallShip[i], maxBullets, numOfSShips, m_player);
			}
			//check for player bullet collisions
			m_col->CheckBVPCollision(m_eBullet, m_player, maxBullets);
		}

		//health check
		if (m_player->health <= 0)
		{
			m_player->lives -= 1;
			m_player->health = m_player->maxHealth;
		}

		// exit the gameState if player has no lives left
		if (m_player->lives < 0)
		{
			quitState = true;
			shutdown();
			gameState = false;
			menuState = true;
			startup();
			quitState = false;

		}
		//pause if player presses pause
		if (input->isKeyDown(aie::INPUT_KEY_ESCAPE)) {
			paused = true;
		}


		//check screen size
		auto window = glfwGetCurrentContext();
		glfwGetWindowSize(window, &screenWidth, &screenHeight);
	}
	if (paused == true)
	{
		//initialise pause menu
		if (pauseL == false)
		{
			m_pauseMenu = new PauseMenu();
			m_pauseMenu->StartUp();
			pauseL	 = true;
		}
		else if(pauseL == true)
		{
			m_pauseMenu->Pause(paused, quitState);
		}
		if (paused == false && quitState != true) 
		{
			con = true;
			shutdown();
			pauseL  = false;


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

void Game1942App::draw()
{
	clearScreen();
	if (menuState == true)
	{
		m_menu->draw();
	}
	else if (gameState == true)
	{
		if (paused == true)
		{
			m_pauseMenu->Draw(screenWidth, screenHeight);
		}
		// wipe the screen to the background colour
		// begin drawing sprites
		m_2dRenderer->begin();
		// draw your stuff here!
		//draw health bar
		m_bar->Draw(m_2dRenderer);
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
		m_player->Draw(m_2dRenderer, m_font, screenWidth, screenHeight);
		//Draw Enemy 
		for (int i = 0; i < numOfSShips; ++i)
		{
			if (m_smallShip[i]->isAlive == true)
			{
				m_2dRenderer->drawSprite(m_smallShip[i]->texture,
					m_smallShip[i]->pos.x,
					m_smallShip[i]->pos.y,
					m_smallShip[i]->pos.w,
					m_smallShip[i]->pos.h, 0, 2);
			}
		}

		for (int i = 0; i < numOfBg; ++i)
		{
			//draw clouds	
			m_2dRenderer->drawSprite(m_clouds[i]->texture,
				m_clouds[i]->pos.x,
				m_clouds[i]->pos.y, 300, 300, 0, 99);
			//draw land
			m_2dRenderer->drawSprite(m_land[i]->texture,
				m_land[i]->pos.x,
				m_land[i]->pos.y, 300, 300, 0, 100);
		}

		// output some text, uses the last used colour

		// done drawing sprites
		m_2dRenderer->end();


	}
}
