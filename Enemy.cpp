#include "Enemy.hpp"
#include <ctime>
Enemy::~Enemy() {}
Enemy::Enemy(int damage, int initialX, int initialY, int width, int height) : Entity(initialX, initialY, width, height)
{
    this->damage = damage;
    //sprite
    std::string one = "0*0";
	std::string two = "*E*";
	std::string three = "0*0";
	this->sprite.addLine(one);
	this->sprite.addLine(two);
	this->sprite.addLine(three);
}
int Enemy::getDamage() { return this->damage; }
void Enemy::move(int speed){
    srand((unsigned)time(0));
    int xDirection = rand()%2;
    //destra
    if (xDirection == 0){
        this->x+= speed;
    }else{
        this->x-= speed;
    }
    this->y += speed;
}
void Enemy::draw(std::vector<std::vector<char>> &canvas)
{
	this->sprite.draw(canvas, this->x, this->y, this->width, this->height);
}