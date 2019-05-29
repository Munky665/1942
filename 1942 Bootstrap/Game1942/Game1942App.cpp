#include "Game1942App.h"

Game1942App::Game1942App() {

}

Game1942App::~Game1942App() {

}

void Game1942App::Create(Background* Item[], int numOfBg) {
	for (int i = 0; i < numOfBg; ++i) {
		Item[i]->texture = new aie::Texture("./textures/Cloud.png");
	}
}

bool Game1942App::startup() {
	setBackgroundColour(0, 0.51, 2.55, 0.9);
	m_2dRenderer = new aie::Renderer2D();
	player = new Player();
	land = new Background();
	for (int i = 0; i < numOfBg; ++i) {
		backgroundItems[i] = new Background();
	}
	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("./font/consolas.ttf", 32);
	player->playerTexture = new aie::Texture("./textures/player.png");
	land->texture = new aie::Texture("./textures/land.png");
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
		backgroundItems[i]->Move(deltaTime, backgroundItems[i]->cloudSpeed);
	}
	//move land
	land->Move(deltaTime, land->landSpeed);
	//move the player
	player->Move(input, deltaTime);
	player->Contain();
	//move Enemy
	for (int i = 0; i < smallShip.size(); ++i) {
		smallShip[i]->Move(deltaTime);
	}
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Game1942App::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	//Draw Enemy
	for (int i = 0; i < smallShip.size(); ++i) {
		m_2dRenderer->drawSprite(smallShip[i]->texture, smallShip[i]->pos.x, smallShip[i]->pos.y, smallShip[i]->pos.width, smallShip[i]->pos.height, 0, 0);
	}
	//draw land
	m_2dRenderer->drawSprite(land->texture, land->pos.x, land->pos.y, 300, 300, 0, 100);
	//draw clouds
	for (int i = 0; i < numOfBg; ++i) {
			m_2dRenderer->drawSprite(backgroundItems[i]->texture,
				backgroundItems[i]->pos.x,
				backgroundItems[i]->pos.y,300,300,0,100);
		
	}
	//draw player
	m_2dRenderer->drawSprite(player->playerTexture, player->pos.x, player->pos.y, player->pos.width, player->pos.width, 0 , 1);
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}