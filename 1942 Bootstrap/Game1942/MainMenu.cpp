#include "MainMenu.h"



MainMenu::MainMenu()
{

}

MainMenu::~MainMenu()
{
}

void MainMenu::startup() 
{
	m_titleFont = new aie::Font("./font/1942.ttf", 54);
	m_font		= new aie::Font("./font/1942.ttf", 32);
	m_plane		= new aie::Texture("./textures/player.png");
	m_renderer  = new aie::Renderer2D();
	isActive = true;
}

void MainMenu::shutdown() 
{
	delete m_titleFont;
	delete m_font;
	delete m_plane;
	delete m_renderer;
	std::cout << "Main Menu deleted" << std::endl;

}

void MainMenu::Menu(bool &state, bool &quit) 
{
	m_input = aie::Input::getInstance();
	if (instructions == false) {
		if (m_input->wasKeyPressed(aie::INPUT_KEY_UP) && startSelected == true)
		{
			exitSelected = true;
			startSelected = false;
		}
		else if (m_input->wasKeyPressed(aie::INPUT_KEY_UP) && exitSelected == true)
		{
			exitSelected = false;
			startSelected = true;
		}
		if (m_input->wasKeyPressed(aie::INPUT_KEY_DOWN) && startSelected == true)
		{
			exitSelected = true;
			startSelected = false;
		}
		else if (m_input->wasKeyPressed(aie::INPUT_KEY_DOWN) && exitSelected == true)
		{
			exitSelected = false;
			startSelected = true;
		}
	}
	if (m_input->wasKeyPressed(aie::INPUT_KEY_ENTER)) 
	{
		if (startSelected == true)
		{
			instructions = true;
			enterCounter++;
		}
		else if(exitSelected)
			quit = true;
	}
	if (instructions == true)
	{
		if (m_input->wasKeyPressed(aie::INPUT_KEY_ENTER) && enterCounter == 2)
		{
			state = true;
			instructions = false;
			startSelected = true;
			enterCounter = 0;
		}
		if (m_input->wasKeyPressed(aie::INPUT_KEY_ESCAPE))
		{
			instructions = false;
			startSelected = true;
			enterCounter = 0;
		}
	}
}

void MainMenu::draw() 
{
	
	m_renderer->begin();
	m_renderer->drawSprite(m_plane, planePositionX, screenY * 0.5, 360, 400,0,2);
	m_renderer->setRenderColour(1, 1, 1, 1);
	m_renderer->drawText(m_titleFont, "Fighter Pilot", screenX, screenY * 0.5,2);
	if (startSelected == true)
	{
		if (instructions == true) {
			m_renderer->setRenderColour(0, 0, 0, 1);
			m_renderer->drawBox(screenW / 2, screenY / 2, screenW, screenY,0,1);
			m_renderer->setRenderColour(1, 1, 1, 1);
			m_renderer->drawText(m_titleFont, "INSTUCTIONS", screenX, screenY / 2,0);
			m_renderer->drawText(m_font, "- Use Arrow Keys to move", screenX, screenY / 2 - 30);
			m_renderer->drawText(m_font, "- Use space Bar to Fire", screenX, screenY / 2 - 60);
			m_renderer->drawText(m_font, "- bigger bullets mean more damage", screenX, screenY / 2 - 90);
			m_renderer->drawText(m_font, "- smaller bullets mean less damage", screenX, screenY / 2 - 120);
			m_renderer->drawText(m_font, "Press Enter to Continue", screenX + 10, screenY / 2 - 150);
		}
		else if (instructions == false) {
			m_renderer->setRenderColour(1, 0, 0, 1);
		}
	}
	else
		m_renderer->setRenderColour(1, 1, 1, 1);
	if(instructions == false)
		m_renderer->drawText(m_font, "Start Game", screenX + 100, (screenY - 80) * 0.5);
	if (exitSelected == true) 
	{
		m_renderer->setRenderColour(1, 0, 0, 1);
	}
	else 
		m_renderer->setRenderColour(1, 1, 1, 1);
	if (instructions == false) {
		m_renderer->drawText(m_font, "Exit Game", screenX + 100, (screenY - 140) * 0.5);
	}
	m_renderer->end();

}
void MainMenu::Reset() {

}