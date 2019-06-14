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

	float m_speed				= 500;
	int m_sBuffer				= 45;

	float m_rightOfWindow		= 1250;
	float m_leftOfWindow		= 30;
	float m_livesPosX			= 40;
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
	
	int score				= 0;
	PlayerPos				pos{ 600, 100 };
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

