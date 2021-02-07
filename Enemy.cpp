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
}
int Enemy::getDamage() { return this->damage; }
void Enemy::move(int speed, int screenWidth, int borderWidth)
{
    this->yDirection = rand() % 2;
    //destra
    if (this->yDirection == 0)
    {
        this->y += speed;
    }
    else
    {
        this->y -= speed;
    }
    this->x += speed;
    this->collideLateralWalls(screenWidth, borderWidth);
}
void Enemy::collideLateralWalls(int screenWidth, int borderWidth)
{
    // borderWidth -= 1; //per avere la coordinata dell'ultimo punto del bordo
    if (this->y + this->width >= screenWidth - borderWidth)
    {
        this->y = screenWidth - borderWidth - 1;
    }
    if (this->y <= 0 + borderWidth)
    {
        this->y = borderWidth + 1;
    }
}
bool Enemy::collideBottomWall(int screenHeight, int borderWidth)
{
    // borderWidth -= 1; //per avere la coordinata dell'ultimo punto del bordo
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
        //check collisioni hitbox
        if (this->x<eX + bWidth &&this->x + this->width> eX &&
            this->y<eY + bHeight &&this->y + this->height> eY)
        {
            // 0 = va verso destra
            // 1 = va verso sinistra
            if (this->yDirection == 0)
            {
                this->y -= 1;
            }
            else
            {
                this->y += 1;
            }
        }
    }
}

void Enemy::collideEnemy(std::vector<Enemy> enemies)
{
    // std::vector<Enemy>::iterator enemyIt;
    for (int i = 0; i< enemies.size(); i++)
    {
        Enemy e = enemies[i];
        int bWidth = e.getWidth();
        int bHeight = e.getHeight();
        int eX = e.getX();
        int eY = e.getY();
        //check collisioni hitbox
        if (this->x<eX + bWidth &&this->x + this->width> eX &&
            this->y<eY + bHeight &&this->y + this->height> eY)
        {
            if (this->yDirection == 0)
            {
                this->y -= 1;
            }
            else
            {
                this->y += 1;
            }
        }
    }
}