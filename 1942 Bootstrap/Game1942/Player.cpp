#include "Player.h"



Player::Player()
{
	m_playerTexture = new aie::Texture("./textures/player.png");
	health = maxHealth;
}


Player::~Player()
{
}

void Player::Reset() {
	pos.x = 600;
	pos.y = 100;
	health = maxHealth;
	lives = 3;
}

void Player::Move(aie::Input* input, float deltaTime) {
	
	if (input->isKeyDown(aie::INPUT_KEY_LEFT) && input->isKeyDown(aie::INPUT_KEY_UP) ||
		input->isKeyDown(aie::INPUT_KEY_A) && input->isKeyDown(aie::INPUT_KEY_W))
	{
	pos.x -= m_speed * deltaTime;
	pos.y += m_speed * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_UP) && input->isKeyDown(aie::INPUT_KEY_RIGHT)
		  || input->isKeyDown(aie::INPUT_KEY_W) && input->isKeyDown(aie::INPUT_KEY_D))
	{
	pos.x += m_speed * deltaTime;
	pos.y += m_speed * deltaTime;
	}
	else if (input->isKeyDown(aie::INPUT_KEY_RIGHT) && input->isKeyDown(aie::INPUT_KEY_DOWN)
		||   input->isKeyDown(aie::INPUT_KEY_D) && input->isKeyDown(aie::INPUT_KEY_S))
	{
	pos.x += m_speed * deltaTime;
	pos.y -= m_speed * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_DOWN) && input->isKeyDown(aie::INPUT_KEY_LEFT)
		  || input->isKeyDown(aie::INPUT_KEY_S) && input->isKeyDown(aie::INPUT_KEY_A))
	{
	pos.x -= m_speed * deltaTime;
	pos.y -= m_speed * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_RIGHT)
		  || input->isKeyDown(aie::INPUT_KEY_D))
	{
		 pos.x += m_speed * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_LEFT)
		  || input->isKeyDown(aie::INPUT_KEY_A))
	{
		 pos.x -= m_speed * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_UP)
		  || input->isKeyDown(aie::INPUT_KEY_W))
	{
		 pos.y += m_speed * deltaTime;
	}


	else if (input->isKeyDown(aie::INPUT_KEY_DOWN)
		  || input->isKeyDown(aie::INPUT_KEY_S))
	{
		 pos.y -= m_speed * deltaTime;
	}
	
	
}
//makes sure player stays within confines of window
void Player::Contain(int sWidth, int sHeight) {
	if (pos.x > sWidth - m_sBuffer) {
		pos.x = sWidth - m_sBuffer;
	}
	else if (pos.y > sHeight - m_sBuffer ) {
		pos.y = sHeight - m_sBuffer;
	}
	if (pos.x < m_sBuffer) {
		pos.x = m_sBuffer;
	}		
	if (pos.y < m_sBuffer + m_livesWidthY) {
		pos.y = m_sBuffer + m_livesWidthY;
	}
}
//render score in top left of game window
void Player::Draw(aie::Renderer2D* m_2dRenderer, aie::Font* m_font, int x, int y) {
	char result[64];
	snprintf(result, 64, "Score:%i", score);
	if (score >= 10 && m_scorePosX == m_originalScorePosX) {
		m_scorePosX += m_fontSize;
	}
	else if (score >= 100 && m_scorePosX == m_originalScorePosX + m_fontSize) {
		m_scorePosX += m_fontSize;
	}
	else if (score >= 1000 && m_scorePosX == m_originalScorePosX + (m_fontSize * 2)) {
		m_scorePosX += m_fontSize;
	}
	else if (score >= 10000 && m_scorePosX == m_originalScorePosX + (m_fontSize * 3)) {
		m_scorePosX += m_fontSize;
	}
	m_2dRenderer->drawText(m_font, result, (x - m_scorePosX), (y - m_scorePosY), 0);
	//draw player
	m_2dRenderer->drawSprite(m_playerTexture,
		pos.x,
		pos.y,
		pos.w + 30,
		pos.h + 30, 0, 1);
	//render Lives
	for (int i = 0; i < lives; ++i) {
		switch (i) {
		case 0:
			m_2dRenderer->drawSprite(m_playerTexture, m_livesPosX, y - m_livesPosY, m_livesWidthX, m_livesWidthY);
			break;
		case 1:
			m_2dRenderer->drawSprite(m_playerTexture, m_livesPosX + 50, y - m_livesPosY, m_livesWidthX, m_livesWidthY);
			break;
		case 2:
			m_2dRenderer->drawSprite(m_playerTexture, m_livesPosX + 100, y - m_livesPosY, m_livesWidthX, m_livesWidthY);
			break;
		}

	}
	m_2dRenderer->drawText(m_font, "Lives: ", m_livesPosX - 20, y - 20);
}

void Player::Heal() {
	if (health <= maxHealth && healed == false) {
		health = health + m_heal;
		healed = true;
		if (health >= maxHealth)
			health = maxHealth;
		else
			health = health;
	}
}

