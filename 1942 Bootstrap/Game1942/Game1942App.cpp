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
		if (col->Collision(p, e, s) == true && p->immune == false) {
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
		if (col->Collision(b[j], e, bs) == true) {
			if (e->collided == true) {
				player->score = player->score + e->scoreValue;
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
		if (col->Collision(b[i], p) == true && p->immune == false) {
			p->health -= b[i]->damage;
			b[i]->collided = true;
			p->immune = true;
			std::cout << "Bullet Collided with Player" << std::endl;
		}
	}
}


bool Game1942App::startup() {

	//set background colour
	setBackgroundColour(0, 0.51, 2.55, 0.9);
	
	//create renderer
	m_2dRenderer = new aie::Renderer2D();
	
	//create player
	player = new Player();
	std::cout << "loaded Player" << std::endl;
	
	//create font
	m_font = new aie::Font("./font/consolas.ttf", 32);
	
	//allocate pngs to land in background
	for (int i = 0; i < numOfBg; ++i) {
		land[i].texture = new aie::Texture("./textures/land.png");
	}
	std::cout << "Loaded land" << std::endl;
	//create bullets
	for (int i = 0; i < maxBullets; ++i) {
		bullet.push_back(new Bullet());
		eBullet.push_back(new Bullet());
	}
	std::cout << "loaded Bullets " << std::endl;
	//creates clouds

	Create(backgroundItems, numOfBg);
	std::cout << "Loaded Clouds" << std::endl;
	
	//Create Enemies
	for (int i = 0; i < numOfSShips; ++i) {
		temp = rand() % 2 + 1;
		switch (temp) {
		case 1:
			smallShip.push_back(new SmallShip());
			break;
		case 2:
			smallShip.push_back(new BigShip());
		};
		std::cout << "Loaded Ships" << std::endl;
	}
	return true;
}

void Game1942App::shutdown() {

	delete[] backgroundItems;
	delete[] land;
	delete m_font;
	delete m_2dRenderer;

}

void Game1942App::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();
	int reverse = numOfSShips - 1;

	for (int i = 0; i < numOfSShips; ++i) {
		if (smallShip[i]->isAlive == false) {
			smallShip[i]->Reset(screenWidth, screenHeight);
		}
	}

	//player fire Bullet
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE)) {
		for (int i = 0; i < maxBullets; ++i) {
			if (bullet[i]->exists != true && player->playerFired != true) {
				bullet[i]->PlayerFired(player);
				std::cout << "bullet fired" << std::endl;
			}
		}
	}

	player->playerFired = false;
	//move each bullet that has been fired
	for (int i = 0; i < maxBullets; ++i) {
		if (bullet[i]->exists != false) {

			bullet[i]->Move(deltaTime);

			if (bullet[i]->pos.y > screenHeight) {
				bullet[i]->exists = false;
			}
			else if (bullet[i]->collided == true) {
				bullet[i]->exists = false;
				bullet[i]->collided = false;
			}
		}
		else if (bullet[i]->exists != true) {
			bullet[i]->pos.x = player->pos.x;
			bullet[i]->pos.y = player->pos.y;
		}
	}

	//move background items
	for (int i = 0; i < numOfBg; ++i) {
		backgroundItems[i].Move(deltaTime, backgroundItems[i].cloudSpeed);
		land[i].Move(deltaTime, land[i].landSpeed);

		for (int j = i + 1; j < numOfBg; ++j) {
			if (col->Collision(land[i], land[j]) == true) {
				land[j].pos.x = rand() % screenWidth + 1;
				land[j].pos.y += displacment;
			}

			if (col->Collision(backgroundItems[i], backgroundItems[j]) == true) {
				backgroundItems[j].pos.x = rand() % screenWidth + 1;
				backgroundItems[j].pos.y += displacment;
			}
		}
	}
	//move the player
	player->Move(input, deltaTime);
	player->Contain(screenWidth, screenHeight);
	//move Enemy
	for (int i = 0; i < numOfSShips; ++i)
	{
		if (smallShip[i]->isAlive == true)
		{
			smallShip[i]->Move(deltaTime, screenWidth, screenHeight);
		}
		for (int b = 0; b < maxBullets; ++b) {
			for (int i = 0; i < numOfSShips; ++i)
			{
				if (eBullet[b]->exists != true)
				{
					if (smallShip[i]->hasFired != true)
					{
						eBullet[b]->EnemyFired(smallShip[i]);
					}
				}
			}
		}
	}
	for (int b = 0; b < maxBullets; ++b)
	{
		//move each bullet that has been fired
		if (eBullet[b]->exists != false)
		{

			eBullet[b]->Move(deltaTime);

			if (eBullet[b]->pos.y <= 0)
			{
				eBullet[b]->exists = false;
				eBullet[b]->efire = false;
				std::cout << "bullet removed" << std::endl;
			}
			else if (eBullet[b]->collided != false)
			{
				eBullet[b]->efire = false;
				eBullet[b]->exists = false;
				std::cout << "bullet removed" << std::endl;
			}
		}

	}
	
	//check if player collided with enemy
	if (player->immune == false) {
		for (int i = 0; i < numOfSShips; ++i) {
			CheckPVECollision(player, smallShip[i], numOfSShips);
		}
		//check for player bullet collisions
		for (int i = 0; i < numOfSShips; ++i) {
			CheckBVECollision(bullet, smallShip[i], maxBullets, numOfSShips);
		}
	}
	//check for enemy bullet collisions
	for (int i = 0; i < numOfSShips; ++i) {
		CheckBVPCollision(eBullet, player, maxBullets);
		smallShip[i]->hasFired = false;

	}
	//cese imunity after collision check
	player->immune = false;

	//health check
	if (player->health <= 0) {
		player->lives -= 1;
		player->health = player->maxHealth;
	}

	// exit the application
	if (player->lives <= 0) {
		quit();
	}
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	//check screen size
	auto window = glfwGetCurrentContext();
	glfwGetWindowSize(window, &screenWidth, &screenHeight);
}

void Game1942App::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!

	//draw bullet
	for (int i = 0; i < maxBullets; ++i) {
		if (bullet[i]->exists != false) {
			m_2dRenderer->drawSprite(bullet[i]->texture, bullet[i]->pos.x, bullet[i]->pos.y, bullet[i]->pos.w, bullet[i]->pos.h);
		}
	}
	for (int j = 0; j < maxBullets; ++j) {
		if (eBullet[j]->exists != false) {
			m_2dRenderer->drawSprite(eBullet[j]->texture, eBullet[j]->pos.x, eBullet[j]->pos.y, eBullet[j]->pos.w, eBullet[j]->pos.h);
		}
	}
	//draw lives
	player->RenderLives(m_2dRenderer, m_font, screenHeight);
	player->RenderScore(m_2dRenderer, m_font, screenWidth, screenHeight);
	player->RenderHealth(m_2dRenderer);
	
	//Draw Enemy 
	for (int i = 0; i < numOfSShips; ++i) {
		if (smallShip[i]->isAlive == true) {
			m_2dRenderer->drawSprite(smallShip[i]->texture, smallShip[i]->pos.x, smallShip[i]->pos.y, smallShip[i]->pos.w, smallShip[i]->pos.h, 0, 0);
		}
	}

	for (int i = 0; i < numOfBg; ++i) {
		//draw clouds	
		m_2dRenderer->drawSprite(backgroundItems[i].texture,
				backgroundItems[i].pos.x,
				backgroundItems[i].pos.y,300,300,0,99);
			//draw land
		m_2dRenderer->drawSprite(land[i].texture, land[i].pos.x, 
								 land[i].pos.y, 300, 300, 0, 100);
	}
	//draw player
	m_2dRenderer->drawSprite(player->playerTexture, player->pos.x, player->pos.y, player->pos.w + 30, player->pos.h + 30, 0 , 1);
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

void Game1942App::Pause(aie::Input* input) {

}