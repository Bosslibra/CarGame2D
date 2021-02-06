#include "Bonus.hpp"

Bonus::Bonus(int bonus, int initialX, int initialY, int width, int height) : Entity(initialX, initialY, width, height)
{
    this->bonus = bonus;
    this->sprite.addLine("B");
}

Bonus::~Bonus() {}

int Bonus::getBonus() { return this->bonus; }
void Bonus::move(int speed)
{
    this->x += speed;
}
void Bonus::draw(std::vector<std::vector<char>> &canvas)
{
    this->sprite.draw(canvas, this->x, this->y, this->width, this->height);
}
bool Bonus::collideBottomWall(int screenHeight, int borderWidth)
{
    // borderWidth -= 1; //per avere la coordinata dell'ultimo punto del bordo
    if (this->x >= screenHeight - borderWidth)
    {
        return true;
    }
    return false;
}
// void Bonus::collideEnemy(std::vector<Enemy> enemies)
// {
//     for (int i = 0; i < enemies.size(); i++)
//     {
//         int bWidth = enemies[i].getWidth();
//         int bHeight = enemies[i].getHeight();
//         int eX = enemies[i].getX();
//         int eY = enemies[i].getY();
//         //check collisioni hitbox
//         if (this->x<eX + bWidth &&this->x + this->width> eX &&
//             this->y<eY + bHeight &&this->y + this->height> eY)
//         {
//             return true;
//         }
//     }
// }