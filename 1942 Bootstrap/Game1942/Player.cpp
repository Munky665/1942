#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}


void Player::Move(aie::Input* input, float deltaTime) {
	
	if (input->isKeyDown(aie::INPUT_KEY_LEFT) && input->isKeyDown(aie::INPUT_KEY_UP))
	{
	pos.x -= speed * deltaTime;
	pos.y += speed * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_UP) && input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
	pos.x += speed * deltaTime;
	pos.y += speed * deltaTime;
	}
	else if (input->isKeyDown(aie::INPUT_KEY_RIGHT) && input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
	pos.x += speed * deltaTime;
	pos.y -= speed * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_DOWN) && input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
	pos.x -= speed * deltaTime;
	pos.y -= speed * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_RIGHT)) 
	{
		 pos.x += speed * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		 pos.x -= speed * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_UP))
	{
		 pos.y += speed * deltaTime;
	}


	else if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		 pos.y -= speed * deltaTime;
	}
	
	
}

void Player::Contain() {
	if (pos.x > sWidth - sBuffer) {
		pos.x = sWidth - sBuffer;
	}
	else if (pos.y > sHeight - sBuffer ) {
		pos.y = sHeight - sBuffer;
	}
	if (pos.x < sBuffer) {
		pos.x = sBuffer;
	}
	if (pos.y < sBuffer) {
		pos.y = sBuffer;
	}
}
//render lives in the top right of the screen
void Player::RenderLives(aie::Renderer2D* m_2dRenderer, aie::Font* m_font) {
	//for each life render a small ship in top right
	for (int i = 0; i < lives; ++i) {
		switch (i) {
		case 0:
			m_2dRenderer->drawSprite(playerTexture, livesPosX, livesPosY, livesWidthX, livesWidthY);
			break;
		case 1:
			m_2dRenderer->drawSprite(playerTexture, livesPosX + 50, livesPosY, livesWidthX, livesWidthY);
			break;
		case 2:
			m_2dRenderer->drawSprite(playerTexture, livesPosX + 100, livesPosY, livesWidthX, livesWidthY);
			break;
		}

	}
	m_2dRenderer->drawText(m_font, "Lives: ", livesPosX - 20, livesPosY + 20);
}
//render score in top left of game window
void Player::RenderScore(aie::Renderer2D* m_2dRenderer, aie::Font* m_font, int x, int y) {
	char result[64];
	snprintf(result, 64, "Score:%i", score);
	if (score >= 10 && scorePosX == originalScorePosX) {
		scorePosX += fontSize;
	}
	else if (score >= 100 && scorePosX == originalScorePosX + fontSize) {
		scorePosX += fontSize;
	}
	else if (score >= 1000 && scorePosX == originalScorePosX + (fontSize * 2)) {
		scorePosX += fontSize;
	}
	else if (score >= 10000 && scorePosX == originalScorePosX + (fontSize * 3)) {
		scorePosX += fontSize;
	}
	m_2dRenderer->drawText(m_font, result, (x - scorePosX), (y - scorePosY), 0);
}
