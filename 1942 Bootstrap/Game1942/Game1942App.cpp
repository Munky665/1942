#include "Game1942App.h"

Game1942App::Game1942App() {

}

Game1942App::~Game1942App() {

}



void Game1942App::Create(Background Item[], int num) {
	for (int i = 0; i < num; ++i) {
		if(num == numOfBg)
		Item[i].texture = new aie::Texture("./textures/Cloud.png");
	}
}

void Game1942App::CheckCollision(Player* p, std::vector<Enemy*> e, int s) {
	for (int i = 0; i < s; ++i) {
		col->Collision(p, e);
		if (e[i]->collided == true) {
			e[i]->pos.x = rand() % screenWidth + 1;
			e[i]->pos.y = screenHeight + displacment;
			e[i]->collided = false;
		}
	}
}
void Game1942App::CheckCollision(std::vector<Bullet*> b, std::vector<Enemy*> e, int bs, int es) {
	for (int j = 0; j < bs; j++){
		for (int i = 0; i < es; ++i) {
			if(col->Collision(b[j], e) == true){
				if (e[i]->collided == true) {
					e[i]->pos.x = rand() % screenWidth + 1;
					e[i]->pos.y = screenHeight + displacment;
					e[i]->collided = false;
					player->score += e[i]->scoreValue;
					b[j]->collided = true;
				}
			}
		}
	}
}
void Game1942App::CheckCollision(std::vector<Bullet*> b, Player* p) {

}

bool Game1942App::startup() {
	setBackgroundColour(0, 0.51, 2.55, 0.9);
	m_2dRenderer = new aie::Renderer2D();
	player = new Player();
	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("./font/consolas.ttf", 32);
	for (int i = 0; i < numOfBg; ++i) {
		land[i].texture = new aie::Texture("./textures/land.png");
	}
	Create(backgroundItems, numOfBg);
	for (int i = 0; i < numOfSShips; ++i) {
		temp = rand() % 2 + 1;
		switch (temp) {
		case 1:
			smallShip.push_back(new SmallShip());
			break;
		case 2:
			smallShip.push_back(new BigShip());
			break;
		}
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
	

	//player fire Bullet
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE)) {
		bullet.push_back(new Bullet(player));
		player->playerFired = true;
	}
	//move each bullet that has been fired
	if (player->playerFired != false) {
		for (int i = 0; i < bullet.size(); ++i) {
			bullet[i]->Move(deltaTime);
			if (bullet[i]->pos.y > screenHeight) {
				bullet.erase(bullet.begin() + i);
			}
			else if (bullet[i]->collided == true) {
				bullet.erase(bullet.begin() + i);
			}
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
	player->Contain();
	//move Enemy
	for (int i = 0; i < smallShip.size(); ++i) {
		smallShip[i]->Move(deltaTime);

		eBullet.push_back(new Bullet(smallShip[i]));
		smallShip[i]->hasFired = true;
	}
	for (int i = 0; i < smallShip.size(); ++i) {		
		//move each bullet that has been fired
		if (smallShip[i]->hasFired != false) {
			for (int i = 0; i < eBullet.size(); ++i) {
				eBullet[i]->Move(deltaTime);
				if (eBullet[i]->pos.y > screenHeight) {
					eBullet.erase(eBullet.begin() + i);
				}
				else if (eBullet[i]->collided == true) {
					eBullet.erase(eBullet.begin() + i);
				}
			}
		}
	}

	//check for collisions
	CheckCollision(player, smallShip, smallShip.size());
	if (player->playerFired == true) {
		CheckCollision(bullet, smallShip, bullet.size(), smallShip.size());
	}
	//cese imunity after collision check
	player->immune = false;
	// exit the application
	if (player->lives == 0) {
		quit();
	}
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Game1942App::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	//draw bullet
	if (player->playerFired != false) {
		for (int i = 0; i < bullet.size(); ++i) {
			m_2dRenderer->drawSprite(bullet[i]->texture, bullet[i]->pos.x, bullet[i]->pos.y, bullet[i]->pos.w, bullet[i]->pos.h);
		}
	}
	for (int i = 0; i < smallShip.size(); ++i) {
		if (smallShip[i]->hasFired != false) {
			for (int j = 0; j < eBullet.size(); ++j) {
				m_2dRenderer->drawSprite(eBullet[j]->texture, eBullet[j]->pos.x, eBullet[j]->pos.y, eBullet[j]->pos.w, eBullet[j]->pos.h);
			}
		}
	}
	//draw lives
	player->RenderLives(m_2dRenderer, m_font);
	player->RenderScore(m_2dRenderer, m_font, screenWidth, screenHeight);
	//Draw Enemy
	for (int i = 0; i < smallShip.size(); ++i) {
		m_2dRenderer->drawSprite(smallShip[i]->texture, smallShip[i]->pos.x, smallShip[i]->pos.y, smallShip[i]->pos.w, smallShip[i]->pos.h, 0, 0);
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