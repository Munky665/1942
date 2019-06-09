#include "Enemy.h"



Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Move(float deltaTime) {

}

void Enemy::textureEnemy() {

}

void Enemy::Size() {

}

Enemy* Enemy::Allocate(Enemy enemy[], int size) {
	for (int i = 0; i < size; ++i) {
		if (enemy[i].isAlive != true) {
			enemy[i].isAlive = true;
			return &enemy[i];
		}
	}
	return nullptr;
}