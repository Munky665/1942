#include "GameOver.h"



GameOver::GameOver()
{
	m_font = new aie::Font("./font/1942.ttf", 32);
	m_headerFont = new aie::Font("./font/1942.ttf", 54);
	m_renderer = new aie::Renderer2D();
}


GameOver::~GameOver()
{
	delete m_font;
	delete m_headerFont;
	delete m_renderer;
}

bool GameOver::DeathMenu()
{
	m_input = aie::Input::getInstance();
	//moves highlight up to next button, or to the bottom if at the top
	if (m_input->wasKeyPressed(aie::INPUT_KEY_UP))
	{
		if (selected == 2)
		{
			selected--;
		}
		else if (selected == 1)
		{
			selected = 2;
		}
	}
	//moves highlight down to next button, or to the top if at the bottom
	if (m_input->wasKeyPressed(aie::INPUT_KEY_DOWN))
	{
		if (selected == 1)
		{
			selected++;
		}
		else if (selected == 2)
		{
			selected = 1;
		}
	}
	//select highlighted button
	if (m_input->wasKeyPressed(aie::INPUT_KEY_ENTER)) {
		if (restartSelected == true)
		{
			return true;
		}
		else if (exitSelected == true)
		{
			return false;
		}
	}
	//sets bool based on which button is highlighted
	switch (selected)
	{
	case 1:
		restartSelected = true;
		exitSelected = false;
		break;
	case 2:
		restartSelected = false;
		exitSelected = true;
		break;
	}
}
//draws the text on the screen for the gameover menu
void GameOver::Draw(float x, float y, int score) 
{
	m_renderer->begin();
	m_renderer->setRenderColour(1, 1, 1, 1);
	m_renderer->drawText(m_headerFont, "GAME OVER", (x * 0.5) - 100, y		   * 0.5, 0);
	if (restartSelected == true)
	{
		m_renderer->setRenderColour(0, 0, 0, 1);
	}
	else
	{
		m_renderer->setRenderColour(1, 1, 1, 1);
	}
	m_renderer->drawText(m_font, "Restart",		  (x * 0.5) - 100, (y - 80) * 0.5, 0);
	if (exitSelected == true)
	{
		m_renderer->setRenderColour(0, 0, 0, 1);
	}
	else
	{
		m_renderer->setRenderColour(1, 1, 1, 1);
	}
	m_renderer->drawText(m_font, "Exit",		 (x * 0.5) - 100, (y - 160) * 0.5, 0);
	m_renderer->setRenderColour(1, 1, 1, 1);
	char result[64];
	snprintf(result, 64, "Score:%i", score);
	m_renderer->drawText(m_headerFont, result,		(x * 0.5) - 100, (y * 0.5) + 80, 0);
	m_renderer->end();
}