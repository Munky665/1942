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
	if (m_input->wasKeyPressed(aie::INPUT_KEY_UP) && startSelected == true) 
	{
		exitSelected  = true;
		startSelected = false;
		std::cout << "Exit Selected" << std::endl;
	}
	else if (m_input->wasKeyPressed(aie::INPUT_KEY_UP) && exitSelected == true) 
	{
		exitSelected  = false;
		startSelected = true;
		std::cout << "Start Selected" << std::endl;
	}
	if (m_input->wasKeyPressed(aie::INPUT_KEY_DOWN) && startSelected == true) 
	{
		exitSelected  = true;
		startSelected = false;
		std::cout << "Exit Selected" << std::endl;
	}
	else if (m_input->wasKeyPressed(aie::INPUT_KEY_DOWN) && exitSelected == true)
	{
		exitSelected  = false;
		startSelected = true;
		std::cout << "Start Selected" << std::endl;
	}

	if (m_input->wasKeyPressed(aie::INPUT_KEY_ENTER)) 
	{
		std::cout << "Enter Pressed" << std::endl;
		if (startSelected == true)
		{
			state = true;
		}
		else if(exitSelected)
			quit = true;
	}
}

void MainMenu::draw() 
{
	
	m_renderer->begin();
	m_renderer->drawSprite(m_plane, planePositionX, screenY * 0.5, 360, 400);
	m_renderer->setRenderColour(0, 0, 100, 0.8);
	m_renderer->drawText(m_titleFont, "Fighter Pilot", screenX, screenY * 0.5);
	if (startSelected == true)
	{
		m_renderer->setRenderColour(0, 0, 100, 0.5);
	}
	else
		m_renderer->setRenderColour(0, 0, 100, 0.8);
	m_renderer->drawText(m_font, "Start Game", screenX + 100, (screenY - 80) * 0.5);
	if (exitSelected == true) 
	{
		m_renderer->setRenderColour(0, 0, 100, 0.5);
	}
	else 
		m_renderer->setRenderColour(0, 0, 100, 0.8);
	m_renderer->drawText(m_font, "Exit Game", screenX + 100, (screenY - 140) * 0.5);
	m_renderer->end();
}
void MainMenu::Reset() {

}