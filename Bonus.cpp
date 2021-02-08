#include "Bonus.hpp"

Bonus::~Bonus() {}
Bonus::Bonus(int bonus, int initialX, int initialY, int width, int height) : Entity(initialX, initialY, width, height)
{
    this->bonus = bonus;
    this->sprite.addLine("$");
}

int Bonus::getBonus() { return this->bonus; }
void Bonus::move()
{
    this->x++;
}
void Bonus::draw(std::vector<std::vector<char>> &canvas)
{
    this->sprite.draw(canvas, this->x, this->y, this->width, this->height);
}
void Bonus::remove(std::vector<std::vector<char>> &canvas)
{
    this->sprite.remove(canvas, this->x, this->y, this->width, this->height);
}
bool Bonus::collideBottomWall(int screenHeight, int borderWidth)
{
    if (this->x >= screenHeight - borderWidth)
    {
        return true;
    }
    return false;
}