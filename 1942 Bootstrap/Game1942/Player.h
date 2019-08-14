#pragma once
#include "Vector2.h"
#include "Texture.h"
#include <Renderer2D.h>
#include "Font.h"
#include "Input.h"
class Player
{
	float m_speed				= 500;
	float m_sBuffer				= 50;

	float m_rightOfWindow		= 1250;
	float m_leftOfWindow		= 30;
	int m_livesPosX			= 40;
	float m_livesPosY			= 40;
	float m_livesWidthX			= 40;
	float m_livesWidthY			= 40;
	float m_scorePosX			= 150;
	float m_originalScorePosX	= 150;
	float m_scorePosY			= 20;
	int m_fontSize				= 10;
	float m_heal			    = 20;
	
	
	aie::Texture*			m_playerTexture;
public:
	int health				 = 0;
	int maxHealth			= 100;
	bool healed = false;
	int score				= 0;
	vector2 pos				= { 600, 100 };
	vector2 size			= { 50,60 };
	int lives				= 3;
	bool immune				= false;
	bool playerFired		= false;
	Player();
	void Reset();
	void Move(aie::Input* input, float deltaTime);
	void Draw(aie::Renderer2D* m_2dRenderer, aie::Font* m_font, int x, int y);
	void Contain(int sWidth, int sHeight);
	void Heal();
	~Player();
};

