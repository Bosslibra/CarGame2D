#include <Enemy.hpp>

Enemy::Enemy(int damage, int initialX, int initialY, int width, int height):Entity(initialX, initialY, width, height)
{
    this->damage = damage;
}
int Enemy::getDamage(){return this->damage;}