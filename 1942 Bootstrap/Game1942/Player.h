#pragma once
#include "Texture.h"
#include <Renderer2D.h>
#include "Font.h"
#include "Input.h"
class Player
{

	struct PlayerPos {
		float x, y;
		float h				 = 50;
		float w				 = 60;
	};

	float speed				= 500;
	int sBuffer				= 45;

	float rightOfWindow		= 1250;
	float leftOfWindow		= 30;
	float livesPosX			= 40;
	float livesPosY			= 40;
	float livesWidthX		= 40;
	float livesWidthY		= 40;
	float scorePosX			= 150;
	float originalScorePosX = 150;
	float scorePosY			= 20;
	int fontSize			= 10;



	aie::Texture*			healthBar;
public:
	int health				 = 0;
	int maxHealth			= 100;
	aie::Texture*			playerTexture;
	int score				= 0;
	PlayerPos				pos{ 600, 100 };
	int lives				= 3;
	bool immune				= false;
	bool playerFired		= false;
	Player();

	void Move(aie::Input* input, float deltaTime);
	void RenderLives(aie::Renderer2D* m_2dRenderer, aie::Font* m_font, int y);
	void RenderScore(aie::Renderer2D* m_2dRenderer, aie::Font* m_font, int x, int y);
	void RenderHealth(aie::Renderer2D* renderer);
	void Contain(int sWidth, int sHeight);
	~Player();
};

