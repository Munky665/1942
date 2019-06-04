#pragma once
#include "Texture.h"
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
public:
	PlayerPos pos{ 600, 100 };
	int lives = 3;
	Player();
	aie::Texture* playerTexture;
	void Move(aie::Input* input, float deltaTime);
	void Contain();
	~Player();
};

