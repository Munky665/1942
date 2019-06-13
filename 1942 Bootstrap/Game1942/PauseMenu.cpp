#include "PauseMenu.h"



PauseMenu::PauseMenu()
{
	exists = true;
}


PauseMenu::~PauseMenu()
{
}

void PauseMenu::StartUp()
{
	m_font		 = new aie::Font("./font/1942.ttf", 32);
	m_headerFont = new aie::Font("./font/1942.ttf", 54);
	m_renderer	 = new aie::Renderer2D();

}
void PauseMenu::ShutDown()
{
	delete m_font;
	delete m_headerFont;
	delete m_renderer;
}
void PauseMenu::Pause(bool &con, bool &exit)
{
	m_input		 = aie::Input::getInstance();

	if (m_input->wasKeyPressed(aie::INPUT_KEY_UP)) 
	{
		if (selected == 2) 
		{
			selected--;
		}
		else if(selected == 1)
		{
			selected = 2;
		}
	}
	if (m_input->wasKeyPressed(aie::INPUT_KEY_DOWN)) 
	{
		if (selected == 1)
		{
			selected++;
		}
		else if(selected == 2)
		{
			selected = 1;
		}
	}
	if (m_input->wasKeyPressed(aie::INPUT_KEY_ENTER)) {
		if (conSelected			 == true) 
		{
			con		= false;
			exit	= false;
			released = false;
		}
		else if (exitSelected	 == true)
		{
			con		= false;
			exit	= true;
			selected = 1;
			released = false;
		}
	}
	if (m_input->wasKeyReleased(aie::INPUT_KEY_ESCAPE) && released == false)
	{
		released = true;
	}
	if (m_input->wasKeyPressed(aie::INPUT_KEY_ESCAPE) && released == true)
	{
		con = false;
		exit = false;
		selected = 1;
		released = false;
	}
	switch (selected)
	{
	case 1:
		conSelected		= true;
		exitSelected	= false;
		break;
	case 2:
		conSelected		= false;
		exitSelected	= true;
		break;
	}
}
void PauseMenu::Draw(float x, float y)
{	
	m_renderer->begin();
	m_renderer->setRenderColour(1, 1, 1, 1);
	m_renderer->drawText(m_headerFont, "PAUSED"  , (x * 0.5) - 100, y		   * 0.5, 0);
	if (conSelected == true)
	{
		m_renderer->setRenderColour(0, 0, 0, 1);
	}
	else
	{
		m_renderer->setRenderColour(1, 1, 1, 1);
	}
	m_renderer->drawText(m_font,	   "Continue", (x * 0.5) - 100, (y -  80) * 0.5, 0);
	if (exitSelected == true)
	{
		m_renderer->setRenderColour(0, 0, 0, 1);
	}
	else
	{
		m_renderer->setRenderColour(1, 1, 1, 1);
	}
	m_renderer->drawText(m_font,	   "Exit"	 , (x * 0.5) - 100, (y - 160) * 0.5, 0);
	m_renderer->end();
}