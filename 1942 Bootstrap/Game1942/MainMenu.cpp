#include "MainMenu.h"



MainMenu::MainMenu()
{
	
}

MainMenu::~MainMenu()
{
}

bool MainMenu::startup() {
	
	
	titleFont = new aie::Font("./font/1942.ttf", 54);
	font = new aie::Font("./font/1942.ttf", 32);
	renderer = new aie::Renderer2D();
	return true;
}

void MainMenu::shutdown() {
	
	delete renderer;
	delete font;

}

bool MainMenu::Menu() {
	startup();
	draw();
	input = aie::Input::getInstance();
	std::cout << "menu loaded" << std::endl;
	if (input->wasKeyPressed(aie::INPUT_KEY_UP) && switchy == 0) {
		switchy = 1;
	}
	else if(input->wasKeyPressed(aie::INPUT_KEY_UP) && switchy == 1)
		switchy = 0;
	
	if (input->wasKeyPressed(aie::INPUT_KEY_DOWN) && switchy == 0) {
		switchy = 1;
	}
	else if(input->wasKeyPressed(aie::INPUT_KEY_DOWN) && switchy == 1)
	switchy = 0;
	if (input->wasKeyPressed(aie::INPUT_KEY_ENTER)) {

		switch (switchy) {
		case 0:
			return true;
			break;
		case 1:
			return false;
			break;
}
	}
}

void MainMenu::draw() {
	
	renderer->begin();
	renderer->drawText(font, "Fighter Pilot", screenX * 0.5, screenY * 0.5);
	renderer->drawText(font, "Start Game", screenX * 0.5, (screenY + 40) * 0.5);
	renderer->drawText(font, "Exit Game", screenX * 0.5, (screenY + 40) * 0.5);
	renderer->end();
}