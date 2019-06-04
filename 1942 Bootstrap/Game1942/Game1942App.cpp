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


bool Game1942App::startup() {
	setBackgroundColour(0, 0.51, 2.55, 0.9);
	m_2dRenderer = new aie::Renderer2D();
	player = new Player();
	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("./font/consolas.ttf", 32);
	player->playerTexture = new aie::Texture("./textures/player.png");
	for (int i = 0; i < numOfBg; ++i) {
		land[i].texture = new aie::Texture("./textures/land.png");
	}
	Create(backgroundItems, numOfBg);
	for (int i = 0; i < smallShip.size(); ++i) {
		smallShip[i]->textureEnemy();
	}
	return true;
}

void Game1942App::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void Game1942App::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();
	
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
	}

	//check for collisions between player and 
	for (int i = 0; i < smallShip.size(); ++i) {
		col->Collision(player, smallShip);
			if (smallShip[i]->collided == true) {
				smallShip[i]->pos.x = rand() % screenWidth + 1;
				smallShip[i]->pos.y = screenHeight + displacment;
				smallShip[i]->collided = false;
			}
	}
	//
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