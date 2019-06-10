#pragma once
#include <Input.h>
#include <Texture.h>
#include "Application.h"
#include <Renderer2D.h>
#include <Font.h>
#include <glfw3.h>
#include <iostream>
class MainMenu
{
private:
	aie::Font* font;
	aie::Font* titleFont;
	aie::Renderer2D* renderer;
	aie::Input* input;
	float screenX = 1280;
	float screenY = 720;
	bool Startselected = false;
	bool ExitSelected = false;
	int switchy = 0;
public:
	MainMenu();
	virtual bool startup();
	virtual void shutdown() ;
	bool Menu();
	virtual void draw();
	virtual ~MainMenu();
};

