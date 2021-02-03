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
void Enemy::move(int speed, int screenWidth, int borderWidth){
    srand((unsigned)time(0));
    int yDirection = rand()%2;
    //destra
    if (yDirection == 0){
        this->y+= speed;
    }else{
        this->y-= speed;
    }
    this->x += speed;
    this->collideLateralWalls(screenWidth, borderWidth);
}
void Enemy::collideLateralWalls(int screenWidth, int borderWidth){
    borderWidth -= 1; //per avere la coordinata dell'ultimo punto del bordo
    if (this->y+this->width >= screenWidth - borderWidth){
        this->y = screenWidth - borderWidth - 1;
    }
    if (this->y <= 0 + borderWidth){
        this->y = borderWidth +1;
    }

}
bool Enemy::collideBottomWall(int screenHeight, int borderWidth){
    borderWidth -= 1; //per avere la coordinata dell'ultimo punto del bordo
    if (this->x+this->height >= screenHeight - borderWidth){
        return true;

    }
    return false;
}
void Enemy::draw(std::vector<std::vector<char>> &canvas)
{
	this->sprite.draw(canvas, this->x, this->y, this->width, this->height);
}