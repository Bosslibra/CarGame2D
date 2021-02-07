#include "Enemy.hpp"
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
    this->yDirection = DIR_LEFT;
}
int Enemy::getDamage() { return this->damage; }
void Enemy::move(int screenWidth, int borderWidth)
{
    int dirChangeProb = rand() % 2;
    if (dirChangeProb == 1)
    {
        this->y++;
        this->yDirection = DIR_RIGHT;
    }
    else
    {
        this->y--;
        this->yDirection = DIR_LEFT;
    }
    this->x++;
    this->collideLateralWalls(screenWidth, borderWidth);
}
void Enemy::collideLateralWalls(int screenWidth, int borderWidth)
{
    if (this->y + this->width >= screenWidth - borderWidth - 1)
    {
        this->y = screenWidth - this->width - borderWidth - 1;
    }
    if (this->y < 0 + borderWidth)
    {
        this->y = borderWidth;
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
void Enemy::draw(std::vector<std::vector<char>> &canvas)
{
    this->sprite.draw(canvas, this->x, this->y, this->width, this->height);
}
void Enemy::remove(std::vector<std::vector<char>> &canvas)
{
    this->sprite.remove(canvas, this->x, this->y, this->width, this->height);
}
void Enemy::collideBonus(std::vector<Bonus> bonuses)
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
            collide = true;
            // DIR_RIGHT = va verso destra
            // DIR_LEFT = va verso sinistra
            if (this->yDirection == DIR_RIGHT)
            {
                this->y--;
            }
            else
            {
                this->y++;
            }
        }
    }
}
void Enemy::collideEnemy(std::vector<Enemy> enemies)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        Enemy e = enemies[i];
        int bWidth = e.getWidth();
        int bHeight = e.getHeight();
        int eX = e.getX();
        int eY = e.getY();
        bool collide = false;
        //check collisioni hitbox
        if (this->x<eX + bWidth &&this->x + this->width> eX &&
            this->y<eY + bHeight &&this->y + this->height> eY)
        {
            if (this->yDirection == DIR_RIGHT)
            {
                this->y--;
            }
            else
            {
                this->y++;
            }
        }
    }
}