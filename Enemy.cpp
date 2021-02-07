#include "Enemy.hpp"
#include <iostream>
using namespace std;
Enemy::~Enemy() {}
Enemy::Enemy(int damage, int initialX, int initialY, int width, int height) : Entity(initialX, initialY, width, height)
{
    this->damage = damage;
    //sprite
    string one = "0*0";
    string two = "*E*";
    string three = "0*0";
    this->sprite.addLine(one);
    this->sprite.addLine(two);
    this->sprite.addLine(three);
    this->yDirection = (int)(rand() % 2);
}
int Enemy::getDamage() { return this->damage; }
void Enemy::move(int screenWidth, int borderWidth)
{
    // se yDirection è uguale a 0 allora si sposta verso destra
    // altrimenti sinistra
    if (this->yDirection == 0)
    {
        this->y += 1;
        this->yDirection = 1;
    }
    else
    {
        this->y -= 1;
        this->yDirection = 0;
    }
    this->x++;
    this->collideLateralWalls(screenWidth, borderWidth);
}
void Enemy::collideLateralWalls(int screenWidth, int borderWidth)
{
    if (this->y + this->width >= screenWidth - borderWidth - 1)
    {
        this->y = screenWidth - this->width - borderWidth - 1;
        this->yDirection = 1; //se sbatte contro il muro di destra allora "si gira" e va verso sinistra
    }
    if (this->y <= 0 + borderWidth + 1)
    {
        this->y = borderWidth + 1;
        this->yDirection = 1; //se sbatte contro il muro di sinistra allora "si gira" e va verso destra
    }
}
bool Enemy::collideBottomWall(int screenHeight, int borderWidth)
{
    if (this->x + this->height >= screenHeight - borderWidth)
    {
        return true;
    }
    return false;
}
void Enemy::draw(vector<vector<char>> &canvas)
{
    this->sprite.draw(canvas, this->x, this->y, this->width, this->height);
}
void Enemy::remove(vector<vector<char>> &canvas)
{
    this->sprite.remove(canvas, this->x, this->y, this->width, this->height);
}
void Enemy::collideBonus(vector<Bonus> bonuses)
{
    for (int i = 0; i < bonuses.size(); i++)
    {

        int bWidth = bonuses[i].getWidth();
        int bHeight = bonuses[i].getHeight();
        int eX = bonuses[i].getX();
        int eY = bonuses[i].getY();
        bool collide = false;
        //check collisioni hitbox
        if (this->x<eX + bWidth &&this->x + this->width> eX &&
            this->y<eY + bHeight &&this->y + this->height> eY)
        {
            // 0 = va verso destra
            // 1 = va verso sinistra
            if (this->yDirection == 0)
            {
                this->y--;
                this->yDirection = 1;
            }
            else
            {
                this->y++;
                this->yDirection = 0;
            }
        }
    }
}
void Enemy::collideEnemy(vector<Enemy> enemies)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        Enemy e = enemies[i];
        int eWidth = e.getWidth();
        int bHeight = e.getHeight();
        int eX = e.getX();
        int eY = e.getY();
        bool collide = false;
        //check collisioni hitbox
        if (this->x<eX + eWidth &&this->x + this->width> eX &&
            this->y<eY + bHeight &&this->y + this->height> eY)
        {
            // 0 = va verso destra
            // 1 = va verso sinistra
            if (this->yDirection == 0)
            {
                this->y--;
                this->yDirection = 1;
            }
            else
            {
                this->y++;
                this->yDirection = 0;
            }
        }
    }
}