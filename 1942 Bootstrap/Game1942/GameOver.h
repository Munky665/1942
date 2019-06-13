#pragma once
#include <Renderer2D.h>
#include <Font.h>
#include <Input.h>

class GameOver
{
	aie::Font*			m_font;
	aie::Font*			m_headerFont;
	aie::Renderer2D*	m_renderer;
	aie::Input*			m_input;

	int selected		 = 1;
	bool restartSelected = false;
	bool exitSelected	 = false;
public:
	GameOver();
	bool DeathMenu();
	void Draw(float x, float y, int score);
	~GameOver();
};

