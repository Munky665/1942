#pragma once
#include "Texture.h"
#include <Renderer2D.h>
#include "Font.h"
#include "Input.h"
class Player
{
	struct PlayerPos {
		float x, y;
		float h = 50;
		float w = 60;
	};

	float speed = 500;
	int sWidth = 1280;
	int sHeight = 720;
	int sBuffer = 45;
	float score = 00000000000;
	float rightOfWindow = 1250;
	float leftOfWindow = 30;
	float livesPosX = 40;
	float livesPosY = 680;
	float livesWidthX = 40;
	float livesWidthY = 40;
	float scorePosX = 150;
	float scorePosY = 20;
public:
	PlayerPos pos{ 600, 100 };
	int lives = 3;
	bool immune = false;
	Player();
	aie::Texture* playerTexture;
	void Move(aie::Input* input, float deltaTime);
	void RenderLives(aie::Renderer2D* m_2dRenderer, aie::Font* m_font);
	void RenderScore(aie::Renderer2D* m_2dRenderer, aie::Font* m_font, int x, int y);
	void Contain();
	~Player();
};

