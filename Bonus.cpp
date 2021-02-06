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
// void Bonus::collideEnemy(std::list<Enemy> enemies)
// {
//     std::list<Enemy>::iterator enemyIt;
//     for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
//     {
//         Enemy e = *enemyIt;

//         int bWidth = e.getWidth();
//         int bHeight = e.getHeight();
//         int eX = e.getX();
//         int eY = e.getY();
//         //check collisioni hitbox
//         if (this->x<eX + bWidth &&this->x + this->width> eX &&
//             this->y<eY + bHeight &&this->y + this->height> eY)
//         {
//             if (this->yDirection == 0)
//             {
//                 this->y -= 1;
//             }
//             else
//             {
//                 this->y += 1;
//             }
//         }
//     }
// }