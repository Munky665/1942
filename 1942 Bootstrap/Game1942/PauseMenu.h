#pragma once
#include <Input.h>
#include <Texture.h>
#include "Application.h"
#include <Renderer2D.h>
#include <Font.h>
#include <iostream>

class PauseMenu
{
protected:
	int selected		  = 1;
	bool restartSelected  = false;
	bool conSelected	  = true;
	bool exitSelected	  = false;

public:
	PauseMenu();
	void StartUp();
	void ShutDown();
	void Pause(bool &con, bool &exit);
	void Draw(float x, float y);
	~PauseMenu();

	bool exists = false;

	aie::Font*		 m_font;
	aie::Font*		 m_headerFont;
	aie::Renderer2D* m_renderer;
	aie::Input*		 m_input;
};

