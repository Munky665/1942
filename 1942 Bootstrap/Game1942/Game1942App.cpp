#include "Game1942App.h"

Game1942App::Game1942App() {

}

Game1942App::~Game1942App() {

}




bool Game1942App::startup() 
{
	//if first time loading load menu items
	if (menuState == true && firstpass == true ) 
	{
		//build menu
		setBackgroundColour(0, 0, 0, 1);
		m_menu = new MainMenu();
		m_menu->startup();
		return true;
	}
	//if not the first time loading set screen colour to black, from blue
	else if (menuState == true && firstpass == false) {
		music->stop();
		setBackgroundColour(0, 0, 0, 1);
	}
	if (gameState == true)
	{
		//load items if first time loading
		if (firstpass == true) {
			FirstBoot();
		}
		//reset items if not first time loading
		else {
			ResetItems();
		}
		music->play();
		music->setLoop(true);
			return true;
	}
}

void Game1942App::shutdown() 
{
	//checks if game state is active
	if (gameState == true && paused == false && con != true)
	{
		//delete items from ram
		if (m_gameOver == true) {
			music->stop();
			DeleteFromMemory();
		}
		//deactivates  menu items
		else if (menuState == false) {
			DeActivate();
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
			menuState = false;
			m_menu->isActive = false;
			startup();
			start = clock();
			wait = clock();
		}
		else if (quitState == true) 
		{
			quit();
		}

	}
	//game state
	aie::Input* input = aie::Input::getInstance();
	if (gameState == true && paused == false && deathState == false && menuState == false)
	{

		//counts down to show enemies, then counts down to change to boss state
		BossAndEnemyTimer();
		//set health bar to player health level
		m_bar->SetValue(m_player->health);
		//set damage immunity to false
		m_player->immune = false;
		//reset ships if destroyed or reach bottom of screen
		ResetShips();
		//boss movement is boss state active
		MoveBoss(deltaTime);
		//player fire Bullet one bullet per press
		if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
		{
			for (int i = 0; i < maxBullets; ++i) {
				//plays sound when bullet is activated from player
				if (m_bullet[i]->exists != true && m_player->playerFired != true) 
				{
					m_bullet[i]->PlayerFired(m_player);
					buffer[0].loadFromFile("./Audio/playershoot.wav");
					sound[0].setBuffer(buffer[0]);
					sound[0].setVolume(shootVol);
					sound[0].play();
				}
			}
		}
		//allow the player to fire again
		m_player->playerFired = false;

		//move each bullet that has been fired
		MovePlayerFiredBullets(deltaTime);

		//move background items
		MoveBackground(deltaTime);

		//stop player from being able to fly out of the window bounds
		m_player->Contain(screenWidth, screenHeight - 200);
		//move the player
		m_player->Move(input, deltaTime);

		//move Enemy
		MoveEnemyAndCheckFire(deltaTime);
		//move Enemy Bullets
		MoveEnemyFiredBullets(deltaTime);
		//check collisions if player is not immune
		if (m_player->immune == false)
		{
			CheckPlayerCollision();
			//check for bullet vs enemy collisions
			for (int i = 0; i < numOfSShips; ++i)
			{
				if (m_smallShip[i]->isAlive == true) {
					if (m_col->CheckBVECollision(m_bullet, m_smallShip[i], maxBullets, m_player) == true)
					{
						if (m_smallShip[i]->isAlive == false && m_smallShip[i]->collided == false) {
							buffer[1].loadFromFile("./Audio/explosion.wav");
							sound[1].setBuffer(buffer[1]);
							sound[1].setVolume(explosionVol);
							sound[1].play();
							m_smallShip[i]->collided = true;
							break;
						}
					}
				}
				//when enemy dies check to see if health should spawn
				SpawnHealth(i);

			}
			//check for player bullet collisions
			if (m_col->CheckBVPCollision(m_eBullet, m_player, maxBullets) == true)
			{
				buffer[3].loadFromFile("./Audio/hit.wav");
				sound[3].setBuffer(buffer[3]);
				sound[3].setVolume(hitvol);
				sound[3].play();
			}
		}
		//move and check collision of health
		PickUpHealth(deltaTime);

		//pause if player presses pause
		if (input->wasKeyPressed(aie::INPUT_KEY_ESCAPE)) {
			paused = true;
			music->pause();
		}
		//check screen size
		auto window = glfwGetCurrentContext();
		glfwGetWindowSize(window, &screenWidth, &screenHeight);
		
		if (bossActive == true) {
			//start boss state
			void BossState();
		}

		for (int i = 0; i < 4; ++i) {
			//check how many cannons are left
			if (m_turrets[i]->isAlive == false && m_turrets[i]->toggled == false) {
				cannonDestroyed = cannonDestroyed + 1;
				m_turrets[i]->toggled = true;
			}
		}
		//if all cannons are destroyed end game
		if (cannonDestroyed == 4) {
			deathState = true;
		}
	}
	//enter gameover state when player has no lives left
	if (deathState == true)
	{
		setBackgroundColour(0, 0, 0, 1);
		//start Death State
		DeathState();
	}

	if (paused == true)
	{
		setBackgroundColour(0, 0, 0, 1);
		//Pause game
		PausedState();
	}
	
}

void Game1942App::draw()
{
	// wipe the screen to the background colour
	clearScreen();
	//check if menu should be drawn
	if (menuState == true)
	{
		m_menu->draw();
	}
	//check if gamestate should be drawn
	else if (gameState == true)
	{
		// begin drawing sprites
		m_2dRenderer->begin();
		//check if pause menu should be drawn
		if (paused == true)
		{
			m_pauseMenu->Draw(screenWidth, screenHeight);
		}
		//draws death menu when active
		if (deathState == true) {
			DrawDeathMenu(m_2dRenderer);
		}
		//draw boss when active
		if (bossActive == true) {
			DrawBoss(m_2dRenderer);
		}
		//draw health bar
		m_bar->Draw(m_2dRenderer);
		//draws health pickup
		m_healthPickUp->Draw(m_2dRenderer);
		//draw bullets
		DrawBullets(m_2dRenderer);
		//draw lives
		m_player->Draw(m_2dRenderer, m_font, screenWidth, screenHeight);
		//Draw Enemy 
		if (enemyState == true)
		{
			DrawEnemyShips(m_2dRenderer);
		}
		//draws background it
		DrawBackground(m_2dRenderer);
		// done drawing sprites
		m_2dRenderer->end();
	}
}
//creates all game items in memory
void Game1942App::FirstBoot()
{
	LoadSounds();
	enemyState = false;
	m_boss = new Boss();
	m_healthPickUp = new HealthPickUp();
	m_death = new GameOver();
	m_pauseMenu = new PauseMenu();
	m_pauseMenu->StartUp();
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
		m_land.pushToEnd(new Land());
		m_clouds.pushToEnd(new Clouds());
	}
	//create bullets
	for (int i = 0; i < maxBullets; ++i)
	{
		m_bullet.pushToEnd(new Bullet());
		m_eBullet.pushToEnd(new Bullet());
	}
	//Create Enemies
	for (int i = 0; i < numOfSShips; ++i)
	{
		temp = rand() % 2 + 1;
		switch (temp)
		{
		case 1:
			m_smallShip.pushToEnd(new SmallShip());
			break;
		case 2:
			m_smallShip.pushToEnd(new BigShip());
		};
	}
	for (int i = 0; i < 4; ++i) {
		m_turrets.pushToEnd(new Cannon(i));
	}
	firstpass = false;
}
//resets all games items
void Game1942App::ResetItems()
{
	//reset boss
	m_boss->Reset(0);
	//bossActive = false;
	//reset cannons
	for (int i = 0; i < 4; ++i) {
		m_turrets[i]->Reset(i);
	}
	//reset clouds
	for (int i = 0; i < numOfBg; ++i)
	{
		m_land[i]->Reset();
		m_clouds[i]->Reset();
	}
	//reset bullets
	for (int i = 0; i < maxBullets; ++i)
	{
		m_bullet[i]->Reset();
		m_eBullet[i]->Reset();
	}
	//reset Enemies
	for (int i = 0; i < numOfSShips; ++i)
	{
		m_smallShip[i]->Reset(screenWidth, screenHeight);
	}
	//set screen colour to blue
	setBackgroundColour(0, 0.51, 2.55, 0.9);
	//reset player position
	m_player->Reset();
	//reset health bar
	m_bar->Reset(screenWidth * 0.5f, screenHeight - 20, 400, 20);
	wait = clock();
	enemyState = false;
}
//deactivates game items
void Game1942App::DeActivate() {
	//deactivate background items
	for (int i = 0; i < numOfBg; ++i)
	{
		m_land[i]->Active = false;
		m_clouds[i]->Active = false;
	}
	//deactivate bullets
	for (int i = 0; i < maxBullets; ++i)
	{
		m_bullet[i]->exists = false;
		m_eBullet[i]->exists = false;
	}
	//deactivate Enemies
	for (int i = 0; i < numOfSShips; ++i)
	{
		m_smallShip[i]->isAlive = false;
	}
	m_bar->isActive = false;

}
//starts timers for enemys and boss spawn
void Game1942App::BossAndEnemyTimer()
{
	if (gameState != false && menuState == false) {
		//starts countdown to boss
		duration = (clock() - wait) / (float)CLOCKS_PER_SEC;
		if (duration > bossTimer && bossActive == false) {
			bossActive = true;
			enemyState = false;
			BossState();
		}
		//start timer to turn on enemys
		if (enemyState == false && bossActive == false) {
			duration = (clock() - wait) / (float)CLOCKS_PER_SEC;
			if (duration > startTimer) {
				enemyState = true;
			}
		}
	}
}
//resets enemy ships when they are hit or reach the bottom of the screen
void Game1942App::ResetShips()
{
	//check if ships are alive and reset them if they are not while boss is inactive 
	if (bossActive == false) {
		for (int i = 0; i < numOfSShips; ++i)
		{
			if (m_smallShip[i]->isAlive == false)
			{
				m_smallShip[i]->Reset(screenWidth, screenHeight);
			}
		}
	}
}
//moves the boss and turrets when active
void Game1942App::MoveBoss(float deltaTime)
{
	//move boss and cannons if boss is active
	if (bossActive == true) {
		m_boss->Move(deltaTime);
		for (int i = 0; i < m_turrets.size(); ++i) {
			m_turrets[i]->Move(deltaTime, m_player, m_bullet); 
			if (m_turrets[i]->hasFiredTimer() == true)
			{
				buffer[2].loadFromFile("./Audio/enemyshoot.wav");
				sound[2].setBuffer(buffer[2]);
				sound[2].setVolume(shootVol);
				sound[2].play();
			}
		}
	}
}
//moves player fired bullets up the screen
void Game1942App::MovePlayerFiredBullets(float deltaTime)
{
	for (int i = 0; i < maxBullets; ++i)
	{
		if (m_bullet[i]->exists != false)
		{
			//move bullet if it exists
			m_bullet[i]->Move(deltaTime);
			//remove bullet if it leaves screen
			if (m_bullet[i]->pos.y > screenHeight)
			{
				m_bullet[i]->exists = false;
			}
			//remove bullet if it has collided
			else if (m_bullet[i]->collided == true)
			{
				m_bullet[i]->exists = false;
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
}
//moves enemy fired bullets down the screen
void Game1942App::MoveEnemyFiredBullets(float deltaTime)
{
	for (int b = 0; b < maxBullets; ++b)
	{
		//move each bullet that has been fired
		if (m_eBullet[b]->exists != false && enemyState == true)
		{
			m_eBullet[b]->Move(deltaTime);
			//if bullet passes out of bottom of screen remove
			if (m_eBullet[b]->pos.y <= 0 || m_bullet[b]->pos.y >= screenHeight)
			{
				m_eBullet[b]->collided = false;
				m_eBullet[b]->exists = false;
				m_eBullet[b]->efire = false;
			}
		}

	}
}
//moves background items ie. clouds down the screen
void Game1942App::MoveBackground(float deltaTime)
{
	for (int i = 0; i < numOfBg; ++i)
	{
		m_clouds[i]->Move(deltaTime, m_clouds[i]->cloudSpeed);
		m_land[i]->Move(deltaTime, m_land[i]->landSpeed);

		for (int j = i + 1; j < numOfBg; ++j)
		{
			//check if land collides with one another
			if (m_col->BkgCollision(m_land[i]->pos, m_land[j]->pos) == true)
			{
				m_land[j]->pos.x = rand() % screenWidth + 1;
				m_land[j]->pos.y += displacment;
			}
			//check if clouds collide with one another
			if (m_col->BkgCollision(m_clouds[i]->pos, m_clouds[j]->pos) == true)
			{
				m_clouds[j]->pos.x = rand() % screenWidth + 1;
				m_clouds[j]->pos.y += displacment;
			}
		}
	}
}
//moves enemy and checks if they have fired
void Game1942App::MoveEnemyAndCheckFire(float deltaTime)
{
	for (int i = 0; i < numOfSShips; ++i)
	{
		if (enemyState == true && bossActive == false)
			//pause ship flight and move
			if (m_smallShip[i]->isAlive == true && m_smallShip[i]->hasStopped != true)
			{
				//pause flight randomly at middle of the screen if ship hasn't stopped
				if (m_smallShip[i]->pos.y < screenHeight * 0.5)
				{
					m_smallShip[i]->PauseFlight();
				}
				else
					//move ships down the screen
					m_smallShip[i]->Move(deltaTime, screenWidth, screenHeight);
			}
		//move ship the rest of the way down the screen if it has stopped
			else if (m_smallShip[i]->isAlive == true && m_smallShip[i]->hasStopped == true && bossActive == false)
			{
				m_smallShip[i]->Move(deltaTime, screenWidth, screenHeight);
			}

		//check if enemy has fired bullet
		for (int b = 0; b < maxBullets; ++b)
		{
			if (m_eBullet[b]->exists == true) {
				if (b < maxBullets)
					b++;
				else if (b == maxBullets)
					break;
			}
			else if (m_eBullet[b]->exists == false) {
				for (int j = 0; j < numOfSShips; ++j)
				{
					m_smallShip[j]->WaitToFire();
					if (m_smallShip[j]->hasFired != true && m_smallShip[i]->pos.y < screenHeight && bossActive == false)
					{
						m_eBullet[b]->EnemyFired(m_smallShip[j]);
						buffer[2].loadFromFile("./Audio/enemyshoot.wav");
						sound[2].setBuffer(buffer[2]);
						sound[2].setVolume(shootVol);
						sound[2].play();
						m_smallShip[j]->hasFired = true;
					}

				}
			}
		}
	}
}
//checks if the player has collided with another game object
void Game1942App::CheckPlayerCollision()
{
	for (int i = 0; i < numOfSShips; ++i)
	{
		//check if player collided with enemy
		if (m_smallShip[i]->isAlive == true)
			if (m_col->CheckPVECollision(m_player, m_smallShip[i]) == true)
			{
				buffer[3].loadFromFile("./Audio/hit.wav");
				sound[3].setBuffer(buffer[3]);
				sound[3].setVolume(100);
				sound[3].play();
			}
	}
}
//checks if an enemy has collided with a player bullet or the player
void Game1942App::CheckEnemyCollision(int i)
{
	
}
//spawns health randomly at position of destroyed enemy
void Game1942App::SpawnHealth(int i)
{
	if (m_smallShip[i]->isAlive == false && m_smallShip[i]->collided == true && bossActive == false) {
		m_healthPickUp->SpawnHealth(m_smallShip[i]->pos.x, m_smallShip[i]->pos.y);
	}
}
//moves health down the screen and heals player if collision occurs
void Game1942App::PickUpHealth(float deltaTime)
{
	if (bossActive == false) {
		//move health pickup down the screen
		m_healthPickUp->Move(deltaTime);
		//check if player has collided with the health pick up
		if (m_col->Collision(m_healthPickUp->pos, m_player->pos) == true) {
			m_player->Heal();
			m_healthPickUp->DeActivate();
			m_player->healed = false;
		}
	}
		//health check
	if (m_player->health <= 0)
	{
		m_player->lives -= 1;
		m_player->health = m_player->maxHealth;
		//enter gameover state
		if (m_player->lives < 0) {
			deathState = true;
		}
	}
	if (bossActive == true)
	{
		m_healthPickUp->DeActivate();
	}
}
void Game1942App::LoadSounds()
{
	if (bossActive == false) {
		music = new sf::Music();
		music->openFromFile("./Audio/BackgroundMusic.wav");
	}
	else {
		music->openFromFile("./Audio/bossfight.wav");
		music->play();
	}
	for (int i = 0; i < numberOfSounds; ++i) {
		sound.push_back(sf::Sound());
		buffer.push_back(sf::SoundBuffer());
	}
}
//activates boss and deactivates enemy ships
void Game1942App::BossState()
{
	//deactivate bullets
	for (int i = 0; i < maxBullets; ++i)
	{
		m_eBullet[i]->exists = false;
	}
	//deactivate Enemies
	for (int i = 0; i < numOfSShips; ++i)
	{
		m_smallShip[i]->pos.x = 0;
		m_smallShip[i]->pos.y = 0;
		m_smallShip[i]->isAlive = false;
	}
	//prevent health pickups spawning while boss is active
	m_healthPickUp->DeActivate();
 	music->stop();
	LoadSounds();

}

//ends game, when boss defeated or player defeted
void Game1942App::DeathState()
{
	isDead = m_death->DeathMenu();
	music->stop();
	if (isDead == true) {
		shutdown();
		startup();
		deathState = false;
	}
	if (isDead == false) {
		shutdown();
		gameState = false;
		menuState = true;
		startup();
		deathState = false;
	}
}
//activates pause state
void Game1942App::PausedState()
{
	//initialise pause menu
	m_pauseMenu->Pause(paused, quitState);
	//if continue is selected
	if (paused == false && quitState != true)
	{
		music->play();
		music->setVolume(musicVol);
		con = true;
		setBackgroundColour(0, 0.51, 2.55, 0.9);
	}
	//if exit is selected
	else if (quitState == true)
	{
		shutdown();
		gameState = false;
		menuState = true;
		startup();
		quitState = false;
	}
}
//draws the menu for game over
void Game1942App::DrawDeathMenu(aie::Renderer2D* renderer)
{
	m_bar->Draw(m_2dRenderer);
	m_death->Draw(screenWidth, screenHeight, m_player->score);
}
//draws the boss and boss turrets
void Game1942App::DrawBoss(aie::Renderer2D * renderer)
{
	m_boss->Draw(renderer);
	for (int i = 0; i < m_turrets.size(); ++i) {
		m_turrets[i]->Draw(renderer);
	}
}
//draws bullets
void Game1942App::DrawBullets(aie::Renderer2D * renderer)
{
	for (int i = 0; i < maxBullets; ++i)
	{
		if (m_bullet[i]->exists != false)
		{
			renderer->drawSprite(m_bullet[i]->texture,
				m_bullet[i]->pos.x,
				m_bullet[i]->pos.y,
				m_bullet[i]->size,
				m_bullet[i]->size);
		}
		if (m_eBullet[i]->exists != false && enemyState == true)
		{
			renderer->drawSprite(m_eBullet[i]->texture,
				m_eBullet[i]->pos.x,
				m_eBullet[i]->pos.y,
				m_eBullet[i]->size,
				m_eBullet[i]->size);
		}
	}
}
//draws enemy ships
void Game1942App::DrawEnemyShips(aie::Renderer2D * renderer)
{
	for (int i = 0; i < numOfSShips; ++i)
	{
		if (m_smallShip[i]->isAlive == true)
		{
			renderer->drawSprite(m_smallShip[i]->texture,
				m_smallShip[i]->pos.x,
				m_smallShip[i]->pos.y,
				m_smallShip[i]->size.x,
				m_smallShip[i]->size.y, 0, 2);
		}
	}
}
//draws background items
void Game1942App::DrawBackground(aie::Renderer2D * renderer)
{
	for (int i = 0; i < numOfBg; ++i)
	{
		//draw clouds	
		renderer->drawSprite(m_clouds[i]->texture,
			m_clouds[i]->pos.x,
			m_clouds[i]->pos.y, 300, 300, 0, 99);
		//draw land
		renderer->drawSprite(m_land[i]->texture,
			m_land[i]->pos.x,
			m_land[i]->pos.y, 300, 300, 0, 100);
	}
}
//removes all game objects from memory upon shutdown
void Game1942App::DeleteFromMemory()
{
	delete music;
	delete m_boss;
	m_bullet.~DynamicArray();
	m_eBullet.~DynamicArray();
	m_smallShip.~DynamicArray();
	m_turrets.~DynamicArray();
	delete m_bar;
	delete m_menu;
	delete m_pauseMenu;
	delete m_death;
	m_clouds.~DynamicArray();
	m_land.~DynamicArray();
	delete m_player;
	delete m_font;
	delete m_2dRenderer;
}
