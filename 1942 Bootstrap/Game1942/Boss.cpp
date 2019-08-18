#include "Boss.h"



void Boss::addChild(Boss * child)
{
	//make sure no parent exists
	assert(child->parent == nullptr);
	//assign "this as parent
	child->parent = this;
	//add new child to vector
	children.push_back(child);
}

Boss::Boss()
{
	m_renderer	= new aie::Renderer2D();
	m_texture	= new aie::Texture("./textures/BossBase.png");
	localTransform[2] = { m_xPosition, m_startingY, 1 };
}


Boss::~Boss()
{
}


void Boss::Move(float deltaTime)
{
	//move from starting position to inposition
	if (inPosition == false) {
		if (parent != nullptr) {
			if (parent->localTransform[2].y > stopPosition) 
			{
				//move child object relative to parent object
				localTransform.translate(0, -moveDown.y * deltaTime);
			}
			else
			{
				inPosition = true;
				right = true;
			}
		}
		else
		{
			if (localTransform[2].y > stopPosition) {
				//moves parent object down the screen
				localTransform.translate(0, -moveDown.y * deltaTime);
			}
			else
			{
				inPosition = true;
				right = true;
			}
		}
	}

	//move to right when in position
	if (right == true) {

		if (parent != nullptr) {
			//if parent in position move cannons to left of screen
			if (parent->localTransform[2].x < screenLeft)
			{
				right = false;
				left = true;

			}
			else
			{
				localTransform.translate(-movement.x* deltaTime, 0);
			}
		}
		else
		{
			//move parent to left of screen when in position
			if (localTransform[2].x < screenLeft)
			{
				left = true;
				right = false;
			}

			else
			{
				localTransform.translate(-movement.x* deltaTime, 0);

			}
		}

	}

	//move to left if in position
	else if (left == true)
	{
		if (parent != nullptr) {
			//if parent at left of screen move cannons right
			if (parent->localTransform[2].x > screenRight)
			{
				left = false;
				right = true;
			}

			else
			{
				localTransform.translate(movement.x* deltaTime, 0);

			}
		}
		else {
			//move parent right
			if (localTransform[2].x > screenRight)
			{
				left = false;
				right = true;
			}

			else
			{
				localTransform.translate(movement.x* deltaTime, 0);

			}
		}
	}
	updateTransform();
}

void Boss::Draw(aie::Renderer2D* renderer)
{
	renderer->drawSpriteTransformed3x3(m_texture, (float*)&globalTransform, 0, 0, 49);

}

void Boss::Reset(int i) {
	inPosition = false;
	left = false;
	right = false;
	localTransform[2].x = m_xPosition;
	localTransform[2].y = m_startingY;
	updateTransform();
}


void Boss::updateTransform()
{
	if (parent != nullptr)
	{
		globalTransform = parent->globalTransform * localTransform;
	}
	else
	{
		globalTransform = localTransform;
	}

	for (auto child : children)
	{
		child->updateTransform();
	}
}
void Boss::translate(float x, float y)
{
	localTransform.translate(x, y);
	updateTransform();
}