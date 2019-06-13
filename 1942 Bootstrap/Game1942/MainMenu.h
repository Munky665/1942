#pragma once
#include <Input.h>
#include <Texture.h>
#include "Application.h"
#include <Renderer2D.h>
#include <Font.h>
#include <iostream>
class MainMenu
{
private:

	float screenX			= 100;
	float screenY			= 720;
	float planePositionX	= 900;
	bool startSelected		= true;
	bool exitSelected		= false;
	int switchy = 0;

public:
	MainMenu();
	void startup();
	void shutdown();
	void Menu(bool &state, bool &quit);
	void Reset();
	void draw();
	 ~MainMenu();
	 bool isActive = false;
	 aie::Texture*		m_plane;
	 aie::Font*			m_font;
	 aie::Font*			m_titleFont;
	 aie::Renderer2D*	m_renderer;
	 aie::Input*		m_input;
};

